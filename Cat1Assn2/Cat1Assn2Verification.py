x = []
y = []
z = []
sum_div_3 = 0
sum_not_div_3 = 0

for n in range(11,110):
    x.append(n)
    if n % 3 == 0:
        y.append(n)
        sum_div_3 += n
    else:
        z.append(n)
        sum_not_div_3 += n

print('Numbers stored in X:')
print(x)

print('\nNumbers stored in Y:')
print(y)
print('Sum of numbers divisible by 3: {} '.format(sum_div_3))

print('\nNumbers stored in Z:')
print(z)
print('Sum of numbers divisible by 3: {}'.format(sum_not_div_3))
