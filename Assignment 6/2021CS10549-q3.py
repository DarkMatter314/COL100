global orderID
global bill
orderIDs = []
bill = []

def call(c):
    for i in range(0,len(c)):
        if("Highest" in c[i]): Highest()
        elif("Serve" in c[i]): Serve()
        else:
            x, y, z = c[i].split()
            y = int(y)
            z = int(z)
            Order(y,z)

def Order(orderID : int, BillValue : int):
    orderIDs.append(orderID)
    bill.append(BillValue)

def Highest():
    if(len(orderIDs) == 0): print("Invalid")
    else:
        maxID = bill.index(max(bill))
        print(orderIDs[maxID])    

def Serve():
    if(len(orderIDs) == 0): print("Invalid")
    else:
        maxID = bill.index(max(bill))
        orderIDs.pop(maxID)
        bill.pop(maxID)

n = int(input())
command = [""]*n
for i in range(n): command[i] = input()
call(command)