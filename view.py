#!/usr/bin/python3

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#:set fileformat=unix
#!!!!!!!!!!!!!!!!!!!!!!!!!!!

'''
*Michal Chorobik 0937145
*CIS 2750 Assignment2
*mchorobi@uofguelph.mail.ca
*February 19, 2017
'''

if __name__ == "__main__":

    import sys
    import glob
    import os
    import curses

def writeFile(postNum,user,stream):#{

    
    oldPosNum="0"

    from subprocess import check_output
    check_output(["./db", "7", user, stream, str(postNum)])
#}

def main(m,var,var2,var3,var4,postNum):#{

    lastRead=0
    lastPost=0
    userName = sys.argv[1]
    choice = sys.argv[2]

    #print("1<br>2<br>3<br>4<br>5<br>6<br>7<br>8<br>9<br>10")
    thePost="<br>"
    array=[]
    array2=[]

    from subprocess import check_output
    out = check_output(["./db", "4", userName, choice, "0"])
    out=out.decode('utf-8')
    mylist = out.split(',')
    #print("python returned output is =",mylist,"=. ")

    list = mylist[:]

    if not list:
        print("<br>This user is not in any streams")
        sys.exit()

    #print(" ".join(list) ,"all ")
    #if choice=="all":
    #    print("0")
    #    sys.exit()

    if var=="0":
        pas=0
        while pas==0:
            for x in range(len(list)):
                if choice in list[x]:
                    pas=1
                if choice == "all":
                    pas=1
            if pas==0:
                print("0")
                sys.exit()

    else:
        choice=var

    if var2=="1":
        pas=0
        while pas==0:
            choice = input()
            for x in range(len(list)):
                if choice in list[x]:
                    pas=1
                if choice == "all":
                    pas=1
            if pas==0:
                print("This is not a possible option")

    if choice!="all":

        from subprocess import check_output
        out = check_output(["./db", "5", userName, choice, "0"])
        out=out.decode('utf-8')
        #print("2python returned output is =",out,"=. ")

        viewLine=out
        u=int(out)

    #curses
    mypad_pos = 0

    count=0
    dateList=[]
    senderList=[]
    oldLine=0
    nextLoop=0
    authorLine=""

    p=1
    ok=20

    if var3=="1":

        if choice == "all":

            from subprocess import check_output
            out = check_output(["./db", "9", userName, choice, "0"])
            out=out.decode('utf-8')
            mylist = out.split('\n')

            messageStr=""
            dateStr=""
            nextLoop=5

            for line in mylist:
               if "Sender" in line:

                   if nextLoop!=5:
                     senderList.append(authorLine+dateStr+messageStr)
                     senderList.sort()

                   authorLine=line[8:]
                   authorLine=authorLine+"<br>"

                   messageStr=""
                   nextLoop=1
               elif nextLoop==1:
                  dateStr=line
                  dateStr=dateStr+"<br>"
                  nextLoop=2
               elif nextLoop==2:
                  messageStr=messageStr+line
                  messageStr=messageStr+"<br>"

            senderList.append(authorLine+dateStr+messageStr)
            senderList.sort()

            for x in senderList:
                    x="<br>Sender: "+x
                    array.append(x)
                    array2.append(x)

            viewLine="0"


        else:

            from subprocess import check_output
            out = check_output(["./db", "6", userName, choice, "0"])
            out=out.decode('utf-8')
            mylist = out.split('\n')

            messageStr=""
            dateStr=""
            nextLoop=5

            #file=choice+"Stream.txt"
            #with open(file,'r') as f:
            for line in mylist:

               if "Sender" in line:

                   if nextLoop!=5:
                     senderList.append(authorLine+dateStr+messageStr)
                     senderList.sort()

                   authorLine=line[8:]
                   authorLine=authorLine+"<br>"

                   messageStr=""
                   nextLoop=1
               elif nextLoop==1:
                  dateStr=line
                  dateStr=dateStr+"<br>"
                  nextLoop=2
               elif nextLoop==2:
                  messageStr=messageStr+line
                  messageStr=messageStr+"<br>"

            senderList.append(authorLine+dateStr+messageStr)
            senderList.sort()

            newLine=""

            for x in senderList:
                    x="<br>Sender: "+x
                    array.append(x)
                    array2.append(x)

    elif choice=="all":

        #for i in range(len(list)): #example: dogs_0,cats_0
            #file=list[i]+"Stream.txt"
            #with open(file,'r') as f:
            from subprocess import check_output
            out = check_output(["./db", "9", userName, choice, "0"])
            out=out.decode('utf-8')


            mylist = out.split('\n')

            if out=="":
              print("<br>This stream is empty")
              sys.exit()

            messageStr=""
            dateStr=""
            nextLoop=5

            for line in mylist:
               if "Sender" in line:
                   authorLine="<br>"+line+"<br>"

                   if nextLoop!=5:
                     array2.append(authorLine+dateStr+messageStr)

                   messageStr=""
                   nextLoop=1
               elif nextLoop==1:
                  dateStr=line
                  dateStr=dateStr+"<br>"
                  nextLoop=2
               elif nextLoop==2:
                  messageStr=messageStr+line
                  messageStr=messageStr+"<br>"

            array2.append(authorLine+dateStr+messageStr)

            viewLine="0"

    else:

        from subprocess import check_output
        out = check_output(["./db", "6", userName, choice, "0"])
        out=out.decode('utf-8')
        #print("3python returned output is =",out,"=. ")

        for line in out:
          line.strip()
          if(line=='\n'):
            thePost+="<br>"
            array.append(thePost)
            thePost=""
            count+=1
          else:
            thePost+=line

        #array.append(thePost)
        #print(array) 

        post=""

        for i in range(len(array)):
            if((i!=0)and(array[i].find("Sender")==-1)):
                post+=array[i]
            else:
                if(i!=0):
                    array2.append(post)
                post=""
                post+=array[i]
            if(i==len(array)-1):
                array2.append(post)

    if choice!="all":
      postNum+=int(viewLine)

    if not array2:
      print("<br>This stream is empty")

    #array2[0]=array2[0][4:]
    array2.append("<br>no unread messages left")

    if(m=="1"):
        postNum=len(array2)-1

    #print(array2) 

    if((postNum>=0)and(postNum<=len(array2))):
        array2[postNum]=array2[postNum].replace("~",' ')
        array2[postNum]=array2[postNum].replace("\"<br>\"",'<br>')
        print(array2[postNum])

    if choice=="all":
      sys.exit()

    if(int(viewLine)>=len(array2)):
        viewLine=len(array2)-2

    if(postNum>=len(array2)):
        postNum=len(array2)-1

    if(var4=='100'):
        writeFile(postNum,userName,choice)
    else:
        writeFile(int(viewLine),userName,choice)

    return 0;

    #}

postNum = sys.argv[3]

#areg4 is mark read all option
# sys.argv[6] is sort

main(sys.argv[5],"0","0",sys.argv[6],sys.argv[4],int(postNum))
