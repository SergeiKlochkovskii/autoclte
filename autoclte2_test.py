#!/usr/bin/env python3
import ctypes

# Load the shared library
autoclte_lib = ctypes.CDLL('./libautoclte2.so')  # Replace with the full path if necessary

# Define the argument and return types for the makeTuxedoCall function
autoclte_lib.makeTuxedoCall.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_size_t]
autoclte_lib.makeTuxedoCall.restype = None


def makeTuxedoCall(input_str):
    # Determine the buffer size based on the input string length
    buffer_size = 8196
    output_buffer = ctypes.create_string_buffer(buffer_size)

    # Call the C function, passing the input and output buffers
    autoclte_lib.makeTuxedoCall(input_str.encode('iso-8859-1'), output_buffer, buffer_size)

    # Decode the output buffer to a Python string
    return output_buffer.value.decode('utf-8')


if __name__ == '__main__':
    input_str = "00000PRUCASER        859001WMDEMOFLOTAS    GRCMATSVC                     00000SVC_FLT 0000000000000000000000000000000000000000000000002551LWX                       00000000        0                                                                                                    770000000000                                                                               "
    output_str = makeTuxedoCall(input_str)

    print(f"Input: {input_str}")
    print(f"Output: {output_str}")

