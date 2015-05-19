import random
import string
N = random.choice(range(1,3));
lens = [1,1,1,1,1,1]
vals = ['1','2','3','4','5','6','7','8','9'];
def cell_gen(size=3, chars=string.ascii_lowercase):
	return ''.join(random.choice(chars) for _ in range(random.choice(lens)))
print N
for k in range(0,N):
	print "" + str(random.choice(range(1,7))) + " " + str(random.choice(range(1,30)))
	for i in range(0,4):
		x = cell_gen()
		for j in range(0,3):
			x += " " + cell_gen()
		print x
	print ""
	
	for i in range(0,4):
		x = random.choice(vals);
		for j in range(0,3):
			x+= " " + random.choice(vals);
		print x
	print ""	
