/*
 * (C) 2007-2017 Alibaba Group Holding Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * See the AUTHORS file for names of contributors.
 *
 */

#ifndef TAIR_COUNTER_WRAPPER_HPP
#define TAIR_COUNTER_WRAPPER_HPP

#include "databuffer.hpp"

namespace tair {
namespace common {
struct counter_wrapper {
    counter_wrapper() {
        memset(this, 0, sizeof(*this));
    }

    counter_wrapper(const counter_wrapper &rhs) {
        memcpy(this, &rhs, sizeof(*this));
    }

    counter_wrapper &operator=(const counter_wrapper &rhs) {
        if (this != &rhs) {
            memcpy(this, &rhs, sizeof(*this));
        }
        return *this;
    }

    bool encode(DataBuffer *output) const {
        output->writeInt64(count);
        output->writeInt64(init_value);
        output->writeInt64(expire);
        return true;
    }

    bool decode(DataBuffer *input) {
        if (!input->readInt64((int64_t *) &count)) return false;
        if (!input->readInt64((int64_t *) &init_value)) return false;
        if (!input->readInt64((int64_t *) &expire)) return false;

        return true;
    }

    size_t encoded_size() {
        return 8 + 8 + 8;
    }

    int64_t count;
    int64_t init_value;
    int64_t expire;
};
}
}
#endif
