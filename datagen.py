from random import random

def rule(x):
	#here x is 1 training dataset
	calcd = (pow((x[0]-2), 2)) + (pow((x[1]-2), 2)/0.3)
	if calcd <= 2:
		return ['1', '0']
	else:
		return ['0', '1']



#print(rule([float(input('Enter x: ')), float(input('Enter y: '))]))
with open('test3.td', 'a+') as file:
	for i in range(10000):
		x = 4 * random()
		y = 4 * random()

		file.write(" ".join([str(x), str(y)]).strip())
		file.write('\n')
		file.write(" ".join(rule([x, y])).strip())
		file.write('\n')