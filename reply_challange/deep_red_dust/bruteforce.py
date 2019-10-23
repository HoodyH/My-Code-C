import zipfile

filename = 'Deep_Red_Dust'
dictionary = 'wordlist.txt'

password = None
file_to_open = zipfile.ZipFile(filename)
with open(dictionary, 'r') as f:
    for line in f.readlines():
        password = line.strip('\n')
        try:
            file_to_open.extractall(pwd=bytes(password, 'utf-8'))
            password = 'Password found: %s' % password
            print(password)
        except Exception as Exc:
            pass
