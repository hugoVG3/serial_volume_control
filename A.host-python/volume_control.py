import serial
import pyautogui

# Set up the serial connection
ser = serial.Serial('COM4', 9600, timeout=0)  # Non-blocking read

# Buffer for incoming messages
message_buffer = ""

while True:
    # Read available data from the serial port
    data = ser.read(ser.in_waiting or 1)  # Read all available bytes or 1 byte
    if data:
        try:
            # Decode and append to the message buffer
            message_buffer += data.decode('utf-8')

            # Process complete commands
            while "U" in message_buffer or "D" in message_buffer or "M" in message_buffer:
                if "U" in message_buffer:
                    pyautogui.press("volumeup")
                    message_buffer = message_buffer.split("U", 1)[1]  # Remove processed command
                elif "D" in message_buffer:
                    pyautogui.press("volumedown")
                    message_buffer = message_buffer.split("D", 1)[1]  # Remove processed command
                elif "M" in message_buffer:
                    pyautogui.press("volumemute")
                    message_buffer = message_buffer.split("M", 1)[1]  # Remove processed command
        except UnicodeDecodeError:
            # Clear buffer if decoding fails
            message_buffer = ""
