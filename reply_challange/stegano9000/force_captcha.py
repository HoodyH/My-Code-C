import requests

res = []
values = []
for val in range(1000, 300000000000):

    while True:
        try:
            r = requests.post(
                url='http://gamebox1.reply.it/ae6cdb9098e1252ec193b2c50587d1b3/{}'.format(val),
                # data='val'
            )
            break
        except ConnectionResetError:
            pass

    if r.text not in res:
        print(r.text)
        res.append(r.text)
        values.append(val)
    print('val {}, len {}'.format(val, len(res)))

print(res)
