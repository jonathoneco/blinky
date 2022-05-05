#!/usr/bin/python3
import struct
import subprocess
import tempfile
import serial


BARS_NUMBER = 100
OUTPUT_BIT_FORMAT = "8bit"

conpat = """
[general]
bars = %d
higher_cutoff_freq = 4000
[output]
method = raw
bit_format = %s
channels = mono
[smoothing]
integral = 0
gravity = 2000
[eq]
1 = 2
2 = 1
3 = 1
"""

config = conpat % (BARS_NUMBER, OUTPUT_BIT_FORMAT)
bytetype, bytesize, bytenorm = ("H", 2, 65535) if OUTPUT_BIT_FORMAT == "16bit" else ("B", 1, 255)


def run():
    ser = serial.Serial("/dev/ttyACM1", 500000)

    with tempfile.NamedTemporaryFile() as config_file:
        config_file.write(config.encode())
        config_file.flush()

        process = subprocess.Popen(["cava", "-p", config_file.name], stdout=subprocess.PIPE)
        chunk = bytesize * BARS_NUMBER
        fmt = bytetype * BARS_NUMBER

        source = process.stdout

        while True:
            data = source.read(chunk)
            if len(data) < chunk:
                print("couldn't read full chunk")
                break
            # sample = [i for i in struct.unpack(fmt, data)]
            # print(sample)

            for x in struct.unpack(fmt, data):
                ser.write(bytes([min(x, 254)]))
                # print(x)
                # ser.write(bytes([1]))

            ser.write(bytes([255]))  # 255 acts as syncing signal
            ser.flush()
            # print(255)

    ser.close()


if __name__ == "__main__":
    run()
