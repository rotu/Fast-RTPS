/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This generated file is licensed to you under the terms described in the
 * _LICENSE file included in this  distribution.
 *
 *************************************************************************
 * 
 * @file Data64kb.h
 * This header file contains the declaration of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifndef _Data64kb_H_
#define _Data64kb_H_

// TODO Poner en el contexto.

#include <stdint.h>
#include <array>
#include <string>
#include <vector>

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#define eProsima_user_DllExport __declspec( dllexport )
#else
#define eProsima_user_DllExport
#endif
#else
#define eProsima_user_DllExport
#endif

#if defined(_WIN32)
#if defined(EPROSIMA_USER_DLL_EXPORT)
#if defined(Data64kb_SOURCE)
#define Data64kb_DllAPI __declspec( dllexport )
#else
#define Data64kb_DllAPI __declspec( dllimport )
#endif // Data64kb_SOURCE
#else
#define Data64kb_DllAPI
#endif
#else
#define Data64kb_DllAPI
#endif // _WIN32

namespace eprosima
{
    namespace fastcdr
    {
        class Cdr;
    }
}

/*!
 * @brief This class represents the structure Data64kb defined by the user in the IDL file.
 * @ingroup DATA64KB
 */
class Data64kb
{
public:

    /*!
     * @brief Default constructor.
     */
    eProsima_user_DllExport Data64kb();
    
    /*!
     * @brief Default destructor.
     */
    eProsima_user_DllExport ~Data64kb();
    
    /*!
     * @brief Copy constructor.
     * @param x Reference to the object Data64kb that will be copied.
     */
    eProsima_user_DllExport Data64kb(const Data64kb &x);
    
    /*!
     * @brief Move constructor.
     * @param x Reference to the object Data64kb that will be copied.
     */
    eProsima_user_DllExport Data64kb(Data64kb &&x);
    
    /*!
     * @brief Copy assignment.
     * @param x Reference to the object Data64kb that will be copied.
     */
    eProsima_user_DllExport Data64kb& operator=(const Data64kb &x);
    
    /*!
     * @brief Move assignment.
     * @param x Reference to the object Data64kb that will be copied.
     */
    eProsima_user_DllExport Data64kb& operator=(Data64kb &&x);

    eProsima_user_DllExport bool operator==(const Data64kb &x) const;
    
    /*!
     * @brief This function copies the value in member data
     * @param _data New value to be copied in member data
     */
    inline eProsima_user_DllExport void data(const std::vector<uint8_t> &_data)
    {
        m_data = _data;
    }

    /*!
     * @brief This function moves the value in member data
     * @param _data New value to be moved in member data
     */
    inline eProsima_user_DllExport void data(std::vector<uint8_t> &&_data)
    {
        m_data = std::move(_data);
    }

    /*!
     * @brief This function returns a constant reference to member data
     * @return Constant reference to member data
     */
    inline eProsima_user_DllExport const std::vector<uint8_t>& data() const
    {
        return m_data;
    }

    /*!
     * @brief This function returns a reference to member data
     * @return Reference to member data
     */
    inline eProsima_user_DllExport std::vector<uint8_t>& data()
    {
        return m_data;
    }
    
    /*!
     * @brief This function returns the maximum serialized size of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getMaxCdrSerializedSize(size_t current_alignment = 0);


    /*!
     * @brief This function serializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serialize(eprosima::fastcdr::Cdr &cdr) const;

    /*!
     * @brief This function deserializes an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void deserialize(eprosima::fastcdr::Cdr &cdr);



    /*!
     * @brief This function returns the maximum serialized size of the Key of an object
     * depending on the buffer alignment.
     * @param current_alignment Buffer alignment.
     * @return Maximum serialized size.
     */
    eProsima_user_DllExport static size_t getKeyMaxCdrSerializedSize(size_t current_alignment = 0);

    /*!
     * @brief This function tells you if the Key has been defined for this type
     */
    eProsima_user_DllExport static bool isKeyDefined();

    /*!
     * @brief This function serializes the key members of an object using CDR serialization.
     * @param cdr CDR serialization object.
     */
    eProsima_user_DllExport void serializeKey(eprosima::fastcdr::Cdr &cdr) const;
    
private:
    std::vector<uint8_t> m_data;
};

#endif // _Data64kb_H_
