import os
import time

def get_user_profile(user_data):
    """ Access user profile (Null Pointer Dereference) """
    return user_data.get("profile").get("name")

def authenticate(username, password):
    """ Authenticate user (Unchecked Return Value) """
    user_db = {"alice": "password123", "bob": "qwerty"}

    if username in user_db and user_db[username] == password:
        return True  # Authentication successful
    else:
        print("Authentication failed")

def transfer_funds(user, recipient, amount):
    """ Transfer funds only if user is authenticated """
    if authenticate(user, "wrongpassword"):  # Authentication failure
        print(f"Transferring {amount} to {recipient}")
    else:
        print("Unauthorized transaction!")


def withdraw_money(user, amount):
    """ Withdraw money from an account after checking balance (TOCTOU Vulnerability) """
    balance_file = f"/tmp/{user}_balance.txt"


    if os.path.exists(balance_file):
        with open(balance_file, "r") as f:
            balance = int(f.read())


        time.sleep(2)


        if balance >= amount:
            with open(balance_file, "w") as f:
                f.write(str(balance - amount))
            print(f"Success: Withdrawn {amount}, New Balance: {balance - amount}")
        else:
            print("Error: Insufficient balance")
    else:
        print("Error: Balance file not found!")



class Session:
    """ User session handling with a Use-After-Free vulnerability """
    def __init__(self, user):
        self.user = user
        self.active = True

    def logout(self):
        """ Log out and free session memory """
        self.active = False
        del self.user

    def get_username(self):
        """ Get username (Use-After-Free Vulnerability) """
        return self.user
