/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-marshal-basic.h  Marshalling routines for basic (primitive) types
 *
 * Copyright (C) 2002  CodeFactory AB
 * Copyright (C) 2004, 2005  Red Hat, Inc.
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef DBUS_MARSHAL_BASIC_H
#define DBUS_MARSHAL_BASIC_H

#include <config.h>
#include <dbus/dbus-protocol.h>
#include <dbus/dbus-types.h>
#include <dbus/dbus-arch-deps.h>
#include <dbus/dbus-string.h>

#ifndef PACKAGE
#error "config.h not included here"
#endif

#ifdef WORDS_BIGENDIAN
#define DBUS_COMPILER_BYTE_ORDER DBUS_BIG_ENDIAN
#else
#define DBUS_COMPILER_BYTE_ORDER DBUS_LITTLE_ENDIAN
#endif

#define DBUS_UINT32_SWAP_LE_BE_CONSTANT(val)	((dbus_uint32_t) (      \
    (((dbus_uint32_t) (val) & (dbus_uint32_t) 0x000000ffU) << 24) |     \
    (((dbus_uint32_t) (val) & (dbus_uint32_t) 0x0000ff00U) <<  8) |     \
    (((dbus_uint32_t) (val) & (dbus_uint32_t) 0x00ff0000U) >>  8) |     \
    (((dbus_uint32_t) (val) & (dbus_uint32_t) 0xff000000U) >> 24)))

#ifdef DBUS_HAVE_INT64

#define DBUS_UINT64_SWAP_LE_BE_CONSTANT(val)	((dbus_uint64_t) (              \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0x00000000000000ff)) << 56) |    \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0x000000000000ff00)) << 40) |    \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0x0000000000ff0000)) << 24) |    \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0x00000000ff000000)) <<  8) |    \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0x000000ff00000000)) >>  8) |    \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0x0000ff0000000000)) >> 24) |    \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0x00ff000000000000)) >> 40) |    \
      (((dbus_uint64_t) (val) &                                                 \
	(dbus_uint64_t) DBUS_UINT64_CONSTANT (0xff00000000000000)) >> 56)))
#endif /* DBUS_HAVE_INT64 */

#define DBUS_UINT32_SWAP_LE_BE(val) (DBUS_UINT32_SWAP_LE_BE_CONSTANT (val))
#define DBUS_INT32_SWAP_LE_BE(val)  ((dbus_int32_t)DBUS_UINT32_SWAP_LE_BE_CONSTANT (val))

#ifdef DBUS_HAVE_INT64
#define DBUS_UINT64_SWAP_LE_BE(val) (DBUS_UINT64_SWAP_LE_BE_CONSTANT (val))
#define DBUS_INT64_SWAP_LE_BE(val)  ((dbus_int64_t)DBUS_UINT64_SWAP_LE_BE_CONSTANT (val))
#endif /* DBUS_HAVE_INT64 */

#ifdef WORDS_BIGENDIAN
#define DBUS_INT32_TO_BE(val)	((dbus_int32_t) (val))
#define DBUS_UINT32_TO_BE(val)	((dbus_uint32_t) (val))
#define DBUS_INT32_TO_LE(val)	(DBUS_INT32_SWAP_LE_BE (val))
#define DBUS_UINT32_TO_LE(val)	(DBUS_UINT32_SWAP_LE_BE (val))
#  ifdef DBUS_HAVE_INT64
#define DBUS_INT64_TO_BE(val)	((dbus_int64_t) (val))
#define DBUS_UINT64_TO_BE(val)	((dbus_uint64_t) (val))
#define DBUS_INT64_TO_LE(val)	(DBUS_INT64_SWAP_LE_BE (val))
#define DBUS_UINT64_TO_LE(val)	(DBUS_UINT64_SWAP_LE_BE (val))
#  endif /* DBUS_HAVE_INT64 */
#else
#define DBUS_INT32_TO_LE(val)	((dbus_int32_t) (val))
#define DBUS_UINT32_TO_LE(val)	((dbus_uint32_t) (val))
#define DBUS_INT32_TO_BE(val)	((dbus_int32_t) DBUS_UINT32_SWAP_LE_BE (val))
#define DBUS_UINT32_TO_BE(val)	(DBUS_UINT32_SWAP_LE_BE (val))
#  ifdef DBUS_HAVE_INT64
#define DBUS_INT64_TO_LE(val)	((dbus_int64_t) (val))
#define DBUS_UINT64_TO_LE(val)	((dbus_uint64_t) (val))
#define DBUS_INT64_TO_BE(val)	((dbus_int64_t) DBUS_UINT64_SWAP_LE_BE (val))
#define DBUS_UINT64_TO_BE(val)	(DBUS_UINT64_SWAP_LE_BE (val))
#  endif /* DBUS_HAVE_INT64 */
#endif

/* The transformation is symmetric, so the FROM just maps to the TO. */
#define DBUS_INT32_FROM_LE(val)	 (DBUS_INT32_TO_LE (val))
#define DBUS_UINT32_FROM_LE(val) (DBUS_UINT32_TO_LE (val))
#define DBUS_INT32_FROM_BE(val)	 (DBUS_INT32_TO_BE (val))
#define DBUS_UINT32_FROM_BE(val) (DBUS_UINT32_TO_BE (val))
#ifdef DBUS_HAVE_INT64
#define DBUS_INT64_FROM_LE(val)	 (DBUS_INT64_TO_LE (val))
#define DBUS_UINT64_FROM_LE(val) (DBUS_UINT64_TO_LE (val))
#define DBUS_INT64_FROM_BE(val)	 (DBUS_INT64_TO_BE (val))
#define DBUS_UINT64_FROM_BE(val) (DBUS_UINT64_TO_BE (val))
#endif /* DBUS_HAVE_INT64 */

#ifndef DBUS_HAVE_INT64
/**
 * An 8-byte struct you could use to access int64 without having
 * int64 support
 */
typedef struct
{
  dbus_uint32_t first32;  /**< first 32 bits in the 8 bytes (beware endian issues) */
  dbus_uint32_t second32; /**< second 32 bits in the 8 bytes (beware endian issues) */
} DBus8ByteStruct;
#endif /* DBUS_HAVE_INT64 */

/**
 * A simple 8-byte value union that lets you access 8 bytes as if they
 * were various types; useful when dealing with basic types via
 * void pointers and varargs.
 */
typedef union
{
  dbus_int32_t  i32;   /**< as int32 */
  dbus_uint32_t u32;   /**< as int32 */
#ifdef DBUS_HAVE_INT64
  dbus_int64_t  i64;   /**< as int32 */
  dbus_uint64_t u64;   /**< as int32 */
#else
  DBus8ByteStruct u64; /**< as 8-byte-struct */
#endif
  double dbl;          /**< as double */
  unsigned char byt;   /**< as byte */
  char *str;           /**< as char* */
} DBusBasicValue;

#ifdef DBUS_DISABLE_ASSERT
#define _dbus_unpack_uint32(byte_order, data)           \
   (((byte_order) == DBUS_LITTLE_ENDIAN) ?              \
     DBUS_UINT32_FROM_LE (*(dbus_uint32_t*)(data)) :    \
     DBUS_UINT32_FROM_BE (*(dbus_uint32_t*)(data)))
#endif

void          _dbus_pack_uint32   (dbus_uint32_t        value,
                                   int                  byte_order,
                                   unsigned char       *data);
#ifndef _dbus_unpack_uint32
dbus_uint32_t _dbus_unpack_uint32 (int                  byte_order,
                                   const unsigned char *data);
#endif

dbus_bool_t   _dbus_marshal_set_basic         (DBusString       *str,
                                               int               pos,
                                               int               type,
                                               const void       *value,
                                               int               byte_order,
                                               int              *old_end_pos,
                                               int              *new_end_pos);
dbus_bool_t   _dbus_marshal_write_basic       (DBusString       *str,
                                               int               insert_at,
                                               int               type,
                                               const void       *value,
                                               int               byte_order,
                                               int              *pos_after);
dbus_bool_t   _dbus_marshal_write_fixed_multi (DBusString       *str,
                                               int               insert_at,
                                               int               element_type,
                                               const void       *value,
                                               int               n_elements,
                                               int               byte_order,
                                               int              *pos_after);
void          _dbus_marshal_read_basic        (const DBusString *str,
                                               int               pos,
                                               int               type,
                                               void             *value,
                                               int               byte_order,
                                               int              *new_pos);
void          _dbus_marshal_read_fixed_multi  (const DBusString *str,
                                               int               pos,
                                               int               element_type,
                                               void             *value,
                                               int               n_elements,
                                               int               byte_order,
                                               int              *new_pos);
void          _dbus_marshal_skip_basic        (const DBusString *str,
                                               int               type,
                                               int               byte_order,
                                               int              *pos);
void          _dbus_marshal_skip_array        (const DBusString *str,
                                               int               element_type,
                                               int               byte_order,
                                               int              *pos);
void          _dbus_marshal_set_uint32        (DBusString       *str,
                                               int               pos,
                                               dbus_uint32_t     value,
                                               int               byte_order);
dbus_uint32_t _dbus_marshal_read_uint32       (const DBusString *str,
                                               int               pos,
                                               int               byte_order,
                                               int              *new_pos);
dbus_bool_t   _dbus_type_is_valid             (int               typecode);
int           _dbus_type_get_alignment        (int               typecode);
dbus_bool_t   _dbus_type_is_basic             (int               typecode);
dbus_bool_t   _dbus_type_is_container         (int               typecode);
dbus_bool_t   _dbus_type_is_fixed             (int               typecode);
const char*   _dbus_type_to_string            (int               typecode);



#endif /* DBUS_MARSHAL_BASIC_H */
