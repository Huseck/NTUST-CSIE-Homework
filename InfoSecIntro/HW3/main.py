import cmd
import logging
import sys
import binascii

from rsa import RSA, RSAKey
import prime
from utils import *

logging.basicConfig(stream=sys.stdout, level=logging.INFO)

try: # python2
    input = raw_input
except: # python3
    input = input

def enhex(s):
    return binascii.hexlify(s)

def unhex(s):
    return binascii.unhexlify(s)

class InteractiveShell(cmd.Cmd):
    def __init__(self):
        cmd.Cmd.__init__(self)

        self.config = {
            "e": '65537'
        }

        key = RSAKey(bits=1024, e=int(self.config['e']))
        print('Default key generated (1024 bits)')
        self.setkey(key)
        self.last = None

    def setkey(self, key):
        self.key = key
        self.cipher = RSA(key)
        key.dump()

    def do_q(self, line):
        """
        quit
        """
        return True

    def do_exit(self, line):
        """
        quit
        """
        return True

    def do_EOF(self, line):
        return True

    def do_set(self, line):
        """
        set key val

        available key:
            e	public exponent
        """

        try:
            key, val = line.split()
        except ValueError:
            print('error while parsing arguments')
            return

        if not key:
            print('key can not be empty')
            return
        self.config[key] = val

    def do_get(self, key):
        """
        get key

        available key:
            e	public exponent
        """

        if not key:
            print('key can not be empty')
            return

        print('%s: %r' % (key, self.config.get(key, None)))

    def do_enc(self, file):
        """
        enc [file]

        keep file empty to read data form stdin
        """

        if not file:
            data = input('Data to encrypt:')
        else:
            try:
                data = open(file, 'rb').read()
            except:
                print('Can not open file %r' % file)
                return

        c = self.cipher.encrypt_data(data)
        self.last = c

        print('Source data: %r...' % data[:256])
        print('Encrypted: %r...' % enhex(c[:256]))

    def do_dec(self, file):
        """
        dec [file]

        keep file empty to read data from stdin
        """

        if not file:
            data = input('Data to decrypt in hex:')
            try:
                data = unhex(data)
            except:
                print('Read input error')
                return
        else:
            try:
                data = open(file, 'rb').read()
            except:
                print('Can not open file %r' % file)
                return

        m = self.cipher.decrypt_data(data)
        self.last = m

        print('Source data: %r...' % data[:256])
        print('Decrypted: %r...' % m[:256])

    def do_keygen(self, bits):
        """
        keygen [bits=1024]
        """
        if not bits: bits = 1024
        try:
            key = RSAKey(bits=int(bits), e=int(self.config['e']))
            self.setkey(key)
        except ValueError:
            print('Can not generate key')

    def do_prime(self, bits):
        """
        prime bits

        generate a prime with n-bits length
        """

        print(prime.randprime_bits(int(bits)))

    def do_dump(self, file):
        """
        dump [file]

        print last result or save last reuslt to file
        """

        if not self.last:
            print('Nothing in last result')
            return

        if file:
            try:
                open(file, 'wb').write(self.last)
            except:
                print('Can not save file')
        else:
            print(enhex(self.last) if type(self.last) is Bytes else self.last)

    def do_loadkey(self, file):
        """
        loadkey [file]

        read key from file or read JSON-format key from stdin
        """

        if file:
            try:
                json_data = open(file, 'rb').read()
            except:
                print('Can not read file')
                return
        else:
            json_data = input('Input JSON-format key:')

        try:
            key = RSAKey.from_json(json_data)
        except Exception as e:
            print('Can not load key, Error show below:')
            print(e)
            return

        self.setkey(key)
        print('Key loaded')

    def do_dumpkey(self, file):
        """
        dumpkey [file]

        dump key to file or stdout
        """

        if file:
            try:
                data = self.key.to_json()
                open(file, 'w').write(data)
            except:
                print('Can not dump key to file')
        else:
            print(self.cipher.key.as_dict())
            self.key.dump()

InteractiveShell().cmdloop()
