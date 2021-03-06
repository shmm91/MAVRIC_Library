Here are a few guidelines regarding code style.

# Automatic formating

[Artistic Style](http://astyle.sourceforge.net/) is used to uniformise indentation, padding, tabulations...

If you use [Sublime Text](https://www.sublimetext.com/), there is a plugin for Artistic Style called [SublimeAStyleFormatter](https://packagecontrol.io/packages/SublimeAStyleFormatter).
The plugin is configured by adding the following lines in the configuration file. Feel free to open an issue to propose changes to this default style.
```yaml
"AStyleFormatter":
{
    "options_default":
    {
        "indent": "spaces",
        "indent-spaces": 4,
        "convert-tabs": true,
        "style": "bsd",
        "indent-switches": true,
        "pad-oper": true,
        "unpad-paren": true,
        "align-pointer": "type",
    },
}

```


# Examples
### File header
```cpp
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
 * \file    filename.cpp
 *
 * \author  MAV'RIC Team
 * \author  Name1
 * \author  Name2
 *
 * \brief   Brief description of the module contained in this file
 *
 * \detail  Detailed description and important information to use this module
 ******************************************************************************/
```

### Function header
```cpp
/**
* \brief Description of what the function does
*
* \param param_name1    description
* \param param2         description
*
* \return description
*/
```


### Structs
```cpp
/**
* \brief Description
*/
typedef struct
{
    type name;          ///< description
    type name2;         ///< description
} MyStruct;
```


### Classes
```cpp
/**
 * \brief   Description of class
 */
class My_new_class: public My_parent_class
{
public:
    /**
     * \brief   Constructor
     *
     * \param   my_param    Description of parameter
     */
    My_new_class(bool my_param);

private:
    int my_private_int      ///< description of my int

    /**
     * \brief   A private member function
     *
     * \return  Success
     */
    bool my_private_member_func(void);
};
```


### Loops
```cpp
while (condition == false)
{
    do_stuff();
}
```


### If
```cpp
if (my_variable > another_variable)
{
    do_this();
}
else
{
    do_that();
}
```