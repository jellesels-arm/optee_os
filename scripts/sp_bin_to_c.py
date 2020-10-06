#!/usr/bin/env python3
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (c) 2017, Linaro Limited
#

import argparse
import array
from elftools.elf.elffile import ELFFile
import os
import re
import struct
import uuid
import zlib


def get_args():
    parser = argparse.ArgumentParser(
        description='Converts a Secure '
        'Partition ELF file into a C source file, ready for '
        'inclusion in the TEE binary as an "early SP".')

    parser.add_argument('--out', required=True,
                        help='Name of the output C file')

    parser.add_argument(
        '--sp',
        required=True,
        help='Path to the SP binary. File name has to be: <uuid>.* '
        'such as: 8aaaf200-2450-11e4-abe2-0002a5d5c51b.stripped.elf')

    parser.add_argument(
        '--compress',
        dest="compress",
        action="store_true",
        help='Compress the SP using the DEFLATE '
        'algorithm')

    return parser.parse_args()


def get_name(obj):
    # Symbol or section .name can be a byte array or a string, we want a string
    try:
        name = obj.name.decode()
    except (UnicodeDecodeError, AttributeError):
        name = obj.name
    return name


def sp_get_flags(sp_f):
    with open(sp_f, 'rb') as f:
        elffile = ELFFile(f)

        for s in elffile.iter_sections():
            if get_name(s) == '.sp_head':
                return struct.unpack('<16x4xI', s.data()[:24])[0]

        raise Exception('.sp_head section not found')


def main():
    args = get_args()

    sp_uuid = uuid.UUID(re.sub(r'\..*', '', os.path.basename(args.sp)))

    with open(args.sp, 'rb') as sp:
        bytes = sp.read()
        uncompressed_size = len(bytes)
        if args.compress:
            bytes = zlib.compress(bytes)
        size = len(bytes)

    f = open(args.out, 'w')
    f.write('/* Generated from ' + args.sp + ' by ' +
            os.path.basename(__file__) + ' */\n\n')
    f.write('#include <compiler.h>\n')
    f.write('#include <kernel/embedded_sp.h>\n\n')
    f.write('__extension__ const struct embedded_ts __embedded_sp_' +
            sp_uuid.hex +
            '\n__embedded_sp __aligned(__alignof__(struct embedded_ts)) = {\n')
    f.write('\t.flags = 0x{:04x},\n'.format(sp_get_flags(args.sp)))
    f.write('\t.uuid = {\n')
    f.write('\t\t.timeLow = 0x{:08x},\n'.format(sp_uuid.time_low))
    f.write('\t\t.timeMid = 0x{:04x},\n'.format(sp_uuid.time_mid))
    f.write('\t\t.timeHiAndVersion = ' +
            '0x{:04x},\n'.format(sp_uuid.time_hi_version))
    f.write('\t\t.clockSeqAndNode = {\n')
    csn = '{0:02x}{1:02x}{2:012x}'.format(sp_uuid.clock_seq_hi_variant,
                                          sp_uuid.clock_seq_low, sp_uuid.node)
    f.write('\t\t\t')
    f.write(', '.join('0x' + csn[i:i + 2] for i in range(0, len(csn), 2)))
    f.write('\n\t\t},\n\t},\n')
    f.write('\t.size = {:d},\n'.format(size))
    if args.compress:
        f.write('\t.uncompressed_size = '
                '{:d},\n'.format(uncompressed_size))
    f.write('\t.ts = {\n')
    i = 0
    while i < size:
        if i % 8 == 0:
            f.write('\t\t')
        f.write(hex(bytes[i]) + ',')
        i = i + 1
        if i % 8 == 0 or i == size:
            f.write('\n')
        else:
            f.write(' ')
    f.write('\t},\n')
    f.write('};\n')
    f.close()


if __name__ == "__main__":
    main()
