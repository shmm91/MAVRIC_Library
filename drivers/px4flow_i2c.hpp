/*******************************************************************************
 * Copyright (c) 2009-2015, MAV'RIC Development Team
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
 * \file px4flow_i2c.hpp
 *
 * \author MAV'RIC Team
 * \author Julien Lecoeur
 *
 * \brief   Driver for PX4Flow optical flow smart camera using I2C
 *
 ******************************************************************************/

#ifndef PX4FLOW_I2C_HPP_
#define PX4FLOW_I2C_HPP_

#include <cstdint>
#include "drivers/px4flow.hpp"
#include "hal/common/i2c.hpp"

class  PX4Flow_i2c: public PX4Flow
{
public:
    /**
     * \brief Configuration
     */
    struct conf_t
    {
        uint8_t       i2c_address;
        orientation_t orientation;
    };

    static const uint8_t GET_FRAME_COMMAND           = 0x0;      ///< Command to receive 22 bytes i2c frame
    static const uint8_t GET_INTEGRAL_FRAME_COMMAND  = 0x16;     ///< Command to receive 25 bytes i2c integral frame

    /**
     * \brief Constructor
     */
    PX4Flow_i2c(I2c& i2c, conf_t config = default_config() );

    /**
     * \brief   Main update function
     *
     * \return  success
     */
    bool update(void);


    /**
     * \brief   Default configuration
     *
     * \return  Configuration structure
     */
    static inline conf_t default_config(void);

protected:
    I2c&                i2c_;                       ///< reference to I2C
    conf_t              config_;                    ///< Configuration
};


/**
 * \brief   Default configuration
 *
 * \return  Configuration structure
 */
PX4Flow_i2c::conf_t PX4Flow_i2c::default_config(void)
{
    conf_t conf = {};

    conf.i2c_address = 0x42;
    conf.orientation = ORIENT_0_DEG;

    return conf;
}

#endif /* PX4FLOW_I2C_HPP_ */
