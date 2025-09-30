/*!A cross-platform build utility based on Lua
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (C) 2015-present, Xmake Open Source Community.
 *
 * @author      ruki
 * @file        rand32.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_MODULE_NAME                "rand32"
#define TB_TRACE_MODULE_DEBUG               (0)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_int_t xm_hash_rand32(lua_State* lua)
{
    // check
    tb_assert_and_check_return_val(lua, 0);

    static union { tb_byte_t b[4]; tb_uint32_t word; } s_seed = {0};
    if (!s_seed.word)
        s_seed.word = (tb_uint32_t)tb_mclock();
    s_seed.word = xm_hash_xorshift32(s_seed.word);

    tb_char_t s[64];
    tb_size_t n = xm_hash_make_cstr(s, s_seed.b, 4);

    lua_pushlstring(lua, s, n);
    return 1;
}
