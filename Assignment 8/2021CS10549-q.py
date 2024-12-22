from typing import Tuple, List
# No other imports allowed

# PART OF THE DRIVER CODE

def input_sudoku() -> List[List[int]]:
	sudoku = list()
	for _ in range(9):
		row = list(map(int, input().rstrip(" ").split(" ")))
		sudoku.append(row)
	return sudoku

def print_sudoku(sudoku:List[List[int]]) -> None:
	for i in range(9):
		for j in range(9):
			print(sudoku[i][j], end = " ")
		print()

# You have to implement the functions below

def get_block_num(sudoku:List[List[int]], pos:Tuple[int, int]) -> int:
	return (pos[0] - (pos[0]-1)%3 + int((pos[1]-1)/3))

def get_position_inside_block(sudoku:List[List[int]], pos:Tuple[int, int]) -> int:
	return ((pos[0]-1)%3)*3 + (pos[1]-1)%3 + 1

def get_block(sudoku:List[List[int]], x: int) -> List[int]:
	rowi = (int((x-1)/3))*3
	coli = (int((x-1)%3))*3
	block = []
	for i in range(rowi, rowi+3):
		for j in range(coli,coli+3):
			block.append(sudoku[i][j])
	return block

def get_row(sudoku:List[List[int]], i: int)-> List[int]:
	row = sudoku[i-1].copy()
	return row

def get_column(sudoku:List[List[int]], x: int)-> List[int]:
	column = []
	for i in range(0, 9):
		column.append(sudoku[i][x-1])
	return column

def find_first_unassigned_position(sudoku : List[List[int]]) -> Tuple[int, int]:
	c = 0
	row = -1
	col = -1
	for i in range(0,len(sudoku)):
		for j in range(0, len(sudoku[i])):
			if(sudoku[i][j] == 0 and c == 0):
				c=1
				row = i + 1
				col = j + 1
	return (row,col)

def valid_list(lst: List[int])-> bool:
	counter = [0 for m in range (0,10)]
	for each in lst:
		for i in range(1,10):
			if each == i: counter[i] += 1
			if(counter[i] > 1): return False
	return True

def valid_sudoku(sudoku:List[List[int]])-> bool:
	for i in range(1,10):
		check = valid_list(get_row(sudoku, i))
		if(check == False): return False
	for i in range(1,10):
		check = valid_list(get_column(sudoku, i))
		if(check == False): return False
	for i in range(1,10):
		check = valid_list(get_block(sudoku, i))
		if(check == False): return False
	return True

def get_candidates(sudoku:List[List[int]], pos:Tuple[int, int]) -> List[int]:
	candidatelist = []
	if(pos == (-1,-1)): return []
	row = get_row(sudoku, pos[0])
	column = get_column(sudoku, pos[1])
	block = get_block(sudoku, get_block_num(sudoku,pos))
	for i in range(1,10):
		if((i not in row) and (i not in column) and (i not in block)): candidatelist.append(i)
	return candidatelist

def make_move(sudoku:List[List[int]], pos:Tuple[int, int], num:int) -> List[List[int]]:
	sudoku[pos[0]-1][pos[1]-1] = num
	return sudoku

def undo_move(sudoku:List[List[int]], pos:Tuple[int, int]):
	sudoku[pos[0]-1][pos[1]-1] = 0
	return sudoku

def sudoku_solver(sudoku: List[List[int]]) -> Tuple[bool, List[List[int]]]:
	""" This is the main Sudoku solver. This function solves the given incomplete Sudoku and returns 
	true as well as the solved sudoku if the Sudoku can be solved i.e. after filling all the empty positions the Sudoku remains valid.
	It return them in a tuple i.e. `(True, solved_sudoku)`.

	However, if the sudoku cannot be solved, it returns False and the same sudoku that given to solve i.e. `(False, original_sudoku)`
	"""
	position = find_first_unassigned_position(sudoku)
	while(position != (-1,-1)):
		candidate = get_candidates(sudoku, position)
		if(len(candidate) == 0): return (False, sudoku)
		for i in range(0, len(candidate)):
			sudoku = make_move(sudoku, position, candidate[i])
			solved,sudoku = sudoku_solver(sudoku)
			if(solved == True): return(True, sudoku)
		if(solved == False): 
			undo_move(sudoku, position)
			return(False, sudoku)
	return(True, sudoku)

# PLEASE NOTE:
# We would be importing your functions and checking the return values in the autograder.
# However, note that you must not print anything in the functions that you define above before you 
# submit your code since it may result in undefined behaviour of the autograder.

def in_lab_component(sudoku: List[List[int]]):
	print("Testcases for In Lab evaluation")
	print("Get Block Number:")
	print(get_block_num(sudoku,(4,4)))
	print(get_block_num(sudoku,(7,2)))
	print(get_block_num(sudoku,(2,6)))
	print("Get Block:")
	print(get_block(sudoku,3))
	print(get_block(sudoku,5))
	print(get_block(sudoku,9))
	print("Get Row:")
	print(get_row(sudoku,3))
	print(get_row(sudoku,5))
	print(get_row(sudoku,9))

# Following is the driver code
# you can edit the following code to check your performance.
if __name__ == "__main__":

	# Input the sudoku from stdin
	sudoku = input_sudoku()

	# Try to solve the sudoku
	possible, sudoku = sudoku_solver(sudoku)

	# The following line is for the in-lab component
	#in_lab_component(sudoku)
	# Show the result of the same to your TA to get your code evaulated

	# Check if it could be solved
	if possible:
		print("Found a valid solution for the given sudoku :)")
		print_sudoku(sudoku)

	else:
		print("The given sudoku cannot be solved :(")
		print_sudoku(sudoku)