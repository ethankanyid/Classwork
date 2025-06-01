import vuln_module
import logging

# Set up logging for suspicious activity
logging.basicConfig(filename='suspicious_inputs.log', level=logging.INFO,
                    format='%(asctime)s - %(message)s')

# Function to monitor input length and detect unusually long strings
def monitor_input(input_string):
    MAX_INPUT_LENGTH = 32  # Define a maximum safe length based on buffer size in the C code

    # Check if the input exceeds a safe length threshold
    if len(input_string) > MAX_INPUT_LENGTH:
        logging.warning(f"Suspicious input detected: Length {len(input_string)} exceeds maximum safe limit.")
        print("Input too long! Potential stack overflow attempt detected. Execution halted.")
        return False

    # If input is safe, return True
    return True

# Wrapper for calling vulnerable_function
def safe_vulnerable_function(input_string):
    if monitor_input(input_string):
        vuln_module.vulnerable_function(input_string)
    else:
        # Optionally, you could return or raise an exception if the input is unsafe
        return

# Example test cases
def test_safe_execution():
    # Safe input (no overflow)
    print("Testing with a safe input...")
    safe_vulnerable_function("Hello, world!")

    # Malicious input (longer than the buffer size)
    print("Testing with a malicious input...")
    long_input = "A" * 64  # Example long input exceeding the safe limit
    safe_vulnerable_function(long_input)

if __name__ == "__main__":
    test_safe_execution()
