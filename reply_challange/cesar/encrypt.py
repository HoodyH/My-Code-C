def encrypt(message, key):
    with open('test_clear.txt', 'rb') as content_file:
        content = content_file.read()
    if len(content) != 256:
        raise Exception('This is a block cipher, messages have to be exactly 256 bytes long')
    ciphertext = list(' ' * 256)
    for i in range(0, 256):
        new_pos = (3 ** (key + i)) % 257
        ciphertext[new_pos - 1] = ((content[i]) ^ i) ^ (new_pos - 1)
    return bytes(ciphertext)


def decrypt(message, key):
    with open(message, 'rb') as content_file:
        cipher_text = content_file.read()

    text = list(' ' * 256)
    rebuilt_position = 0
    for current_pos in range(1, 256):
        # prova tutti i valori
        # fino a quando non trovo quello che genera l'attuale posizione con la chiave corrente
        for try_idx in range(0, 256):
            if (current_pos+1) is (3**(key+try_idx)) % 257:
                rebuilt_position = try_idx

        # prova a recuperare il valore facendo gli xor
        data = cipher_text[current_pos]
        try:
            # val = cipher_text[current_pos] ^ current_pos-1
            # val = val ^ rebuilt_position
            val = (data ^ rebuilt_position) ^ current_pos
            text[rebuilt_position-1] = str(chr(val))
        except:
            print('wrong---------')
            break
            # text[rebuilt_position-1] = str(chr(0))
    return text


def do():
    out_save = []
    for key in range(0, 256):
        out = decrypt('enc.txt', key)
        out_str = ''.join(str(e) for e in out)
        if out_str:
            print('\nkey: {}\n{}\n'.format(key, out_str))
        if str.startswith(out_str.upper(), 'FLG'):
            out_save.append(out_str)
    print('--------------------------------------')
    print(out_save)


def create():
    out = encrypt('', 100)

    with open('test_enc.txt', 'wb') as encryped_file:
        encryped_file.write(out)


do()
