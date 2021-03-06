/*******************************************************************************
 * Copyright (c) 2009-2016, MAV'RIC Development Team
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*******************************************************************************
 * \file periodic_telemetry.cpp
 *
 * \author MAV'RIC Team
 * \author Julien Lecoeur
 *
 * \brief Periodic telemetry
 *
 ******************************************************************************/

#include "communication/periodic_telemetry.hpp"
#include "util/print_util.hpp"

Periodic_telemetry::Periodic_telemetry( Mavlink_stream& mavlink_stream,
                                        Mavlink_message_handler& handler,
                                        conf_t __attribute__((unused)) config):
    mavlink_stream_(mavlink_stream),
    count_(0)
{
    // Add callback to activate / disactivate streams
    handler.add_msg_callback(  MAVLINK_MSG_ID_REQUEST_DATA_STREAM, // 66
                               MAVLINK_BASE_STATION_ID,
                               MAV_COMP_ID_ALL,
                               &toggle_telemetry_stream,
                               this );
}

bool Periodic_telemetry::update(void)
{
    return scheduler().update();
}


bool Periodic_telemetry::sort(void)
{
    return scheduler().sort_tasks();
}


/*************************************************************************
 *                 static member functions                               *
 ************************************************************************/

bool Periodic_telemetry::send_message(telemetry_entry_t* telemetry_entry)
{
    bool success = true;

    mavlink_message_t msg;
    telemetry_entry->function(  telemetry_entry->module,
                                telemetry_entry->mavlink_stream,
                                &msg);

    success &= telemetry_entry->mavlink_stream->send(&msg);

    return success;
}


void Periodic_telemetry::toggle_telemetry_stream(Periodic_telemetry* telemetry, uint32_t sysid, const mavlink_message_t* msg)
{
    // Decode message
    mavlink_request_data_stream_t request;
    mavlink_msg_request_data_stream_decode(msg, &request);

    if (((request.target_system == sysid) || (request.target_system == 0)))
    {
        if (request.req_stream_id == 255)
        {
            // send full list of streams
            telemetry->scheduler().run_all_tasks_now();
        }
        else
        {
            Scheduler_task* task = telemetry->scheduler().get_task_by_id(request.req_stream_id);

            if (task != NULL)
            {
                if (request.start_stop)
                {
                    task->set_run_mode(Scheduler_task::Scheduler_task::RUN_REGULAR);
                }
                else
                {
                    task->set_run_mode(Scheduler_task::Scheduler_task::RUN_NEVER);
                }

                if (request.req_message_rate > 0)
                {
                    task->change_period(Scheduler::TIMEBASE / (uint32_t)request.req_message_rate);
                }
            }
            else
            {
                print_util_dbg_print("This stream ID is not registred and cannot be activated.\r\n");
            }
        } //end of else request.req_stream_id != 255
    }
}
