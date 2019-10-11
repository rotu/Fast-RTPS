/*
 * Copyright 2010, Object Management Group, Inc.
 * Copyright 2019, Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 */

#ifndef OMG_DDS_CORE_XTYPES_SEQUENCE_INSTANCE_HPP_
#define OMG_DDS_CORE_XTYPES_SEQUENCE_INSTANCE_HPP_

#include <dds/core/xtypes/DynamicType.hpp>

#include <cstdint>
#include <cstring>

namespace dds {
namespace core {
namespace xtypes {

class SequenceInstance
{
public:
    SequenceInstance(
            const DynamicType& content,
            uint32_t capacity = 0)
        : content_(content)
        , block_size_(content.memory_size())
        , memory_(capacity > 0 ? new uint8_t[capacity * block_size_] : nullptr)
        , capacity_(capacity)
        , size_(0)
    {}

    SequenceInstance(
            const SequenceInstance& other)
        : content_(other.content_)
        , block_size_(other.block_size_)
        , memory_(other.capacity_ > 0 ? new uint8_t[other.capacity_ * other.block_size_] : nullptr)
        , capacity_(other.capacity_)
        , size_(other.size_)
    {
        if(memory_ != nullptr)
        {
            copy_content(memory_, other.memory_);
        }
    }

    SequenceInstance(
            SequenceInstance&& other)
        : content_(std::move(other.content_))
        , block_size_(std::move(other.block_size_))
        , memory_(std::move(other.memory_))
        , capacity_(std::move(other.capacity_))
        , size_(std::move(other.size_))
    {
        other.memory_ = nullptr;
    }

    bool operator == (
            const SequenceInstance& other) const
    {
        if(content_.is_constructed_type())
        {
            bool comp = true;
            for(uint32_t i = 0; i < size_; i++)
            {
                comp &= content_.compare_instance(memory_ + i * block_size_, other.memory_ + i * block_size_);
            }
            return comp;
        }
        else //optimization when the type is primitive
        {
            return std::memcmp(memory_, other.memory_, size_ * block_size_) == 0;
        }
    }

    virtual ~SequenceInstance()
    {
        if(memory_ != nullptr)
        {
            if(content_.is_constructed_type())
            {
                uint32_t block_size = block_size_;
                for(int32_t i = size_ - 1; i >= 0; i--)
                {
                    content_.destroy_instance(memory_ + i * block_size);
                }
            }

            delete[] memory_;
            memory_ = nullptr;
        }
    }

    uint8_t* push(
            const uint8_t* instance)
    {
        if(size_ == capacity_)
        {
            realloc();
        }

        uint8_t* place = memory_ + size_ * block_size_;
        content_.copy_instance(place, instance);

        size_++;

        return place;
    }

    uint8_t* operator [] (
            uint32_t index) const
    {
        //TODO: debug exception
        return memory_ + index * block_size_;
    }

    uint32_t size() const { return size_; }

private:
    const DynamicType& content_;
    uint32_t block_size_;
    uint8_t* memory_;
    uint32_t capacity_;
    uint32_t size_;

    void realloc()
    {
        uint32_t new_capacity = (capacity_ > 0) ? capacity_ * 2 : 1;
        uint8_t* new_memory = new uint8_t[new_capacity * block_size_];

        move_content(new_memory, memory_);

        delete[] memory_;
        memory_ = new_memory;
        capacity_ = new_capacity;
    }

    void copy_content(
            uint8_t* target,
            const uint8_t* source)
    {
        if(content_.is_constructed_type())
        {
            for(uint32_t i = 0; i < size_; i++)
            {
                content_.copy_instance(target + i * block_size_, source + i * block_size_);
            }
        }
        else //optimization when the type is primitive
        {
            std::memcpy(target, source, size_ * block_size_);
        }
    }

    void move_content(
            uint8_t* target,
            uint8_t* source)
    {
        if(content_.is_constructed_type())
        {
            for(uint32_t i = 0; i < size_; i++)
            {
                content_.move_instance(target + i * block_size_, source + i * block_size_);
            }
        }
        else //optimization when the type is primitive
        {
            std::memcpy(target, source, size_ * block_size_);
        }
    }
};

} //namespace xtypes
} //namespace core
} //namespace dds

#endif //OMG_DDS_CORE_XTYPES_SEQUENCE_INSTANCE_HPP_