from random import randint
import os

TOTAL = 5000
dirs = ''
for i in range(TOTAL):
	flag = randint(1, 4)
	if flag == 1:
		dirs += 'e'
	elif flag == 2:
		dirs += 'w'
	elif flag == 3:
		dirs += 's'
	elif flag == 4:
		dirs += 'n'

case_id = 1
while True:
	print("Case #%d" % case_id)
	case_id += 1
	os.system("./main " + dirs + " > /dev/null")
