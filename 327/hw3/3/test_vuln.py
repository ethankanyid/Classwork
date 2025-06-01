import sys
import vuln_module

def trigger_overflow():
    # This payload is longer than the 32-byte buffer in the C code.
    payload = "A" * 32

    print("[*] Sending payload...")
    try:
        vuln_module.vulnerable_function(payload)
        print("[*] Payload sent successfully. No crash detected.")
    except Exception as e:
        print(f"[!] Exception occurred: {e}")
    else:
        print("[*] Function returned without exception.")

if __name__ == "__main__":
    print("[*] Starting test...")
    try:
        trigger_overflow()
    except KeyboardInterrupt:
        print("[!] Interrupted by user.")
    except:
        print("[!] Something unexpected happened:", sys.exc_info()[0])
    finally:
        print("[*] Test completed.")
