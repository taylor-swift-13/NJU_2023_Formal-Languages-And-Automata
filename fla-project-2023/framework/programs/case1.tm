

; the finite set of states
#Q = {init,check,finda,back,illegal,q0,q1,q2,q3,q4,q5,q6,accept,reject,clean,printI1,printl1,printl2,printe,printg,printa,printl3,print_,printI2,printn,printp,printu,printt}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,_,c,e,s,I,l,e,g,l,n,p,u,t}

; the start state
#q0 = init

; the blank symbol
#B = _

; the set of final states
#F = {accept}

; the number of tapes
#N = 3

; the transition functions


init a__ a__ r** check
init b__ b__ *** illegal
init ___ b__ *** illegal


check a__ a__ r** check
check b__ b__ r** finda
check ___ b__ *** illegal

finda a__ b__ *** illegal
finda b__ b__ r** finda
finda ___ ___ l** back

back a__ a__ l** back
back b__ b__ l** back
back ___ ___ r** q0


q0 a__ as_ *** q1

q1 as_ as_ r*r q1
q1 bs_ cs_ *** q2 ;change first b to c

q2 as_ as_ l** q2 ;mov to left
q2 cs_ cs_ l** q2
q2 a__ a__ l** q2
q2 c__ c__ l** q2
q2 _s_ _s_ r** q3 ;first back to left
q2 ___ ___ r** q3 ;first back to left


q3 as_ as_ rr* q3 ;head3 count b
q3 a__ a__ rr* q3 ;head3 count b
q3 c__ c__ r** q3 ;head2 count i*j
q3 b__ c__ **r q2
q3 ___ _e_ l** q4

q4 ce_ ce_ *l* q4
q4 c__ c__ *l* q4
q4 cs_ cs_ *** q5 ;reset head 2;

q5 as_ as_ l** q5
q5 cs_ cs_ l** q5
q5 _s_ _s_ r** q6 ;reset head 1;

q6 as_ c__ rr* q6
q6 a__ c__ rr* q6
q6 c__ c__ rr* q6
q6 ___ c__ rr* q6
q6 ce_ ___ ll* accept
q6 _e_ ___ ll* accept


illegal b__ b__ l** illegal
illegal c__ c__ l** illegal
illegal a__ a__ l** illegal
illegal ___ b__ *** clean


clean b__ ___ r** clean
clean a__ ___ r** clean
clean ___ ___ *** printI1


printI1 ___ I__ r** printl1
printl1 ___ l__ r** printl2
printl2 ___ l__ r** printe
printe ___ e__ r** printg
printg ___ g__ r** printa
printa ___ a__ r** printl3
printl3 ___ l__ r** print_
print_ ___ ___ r** printI2
printI2 ___ I__ r** printn
printn ___ n__ r** printp
printp ___ p__ r** printu
printu ___ u__ r** printt
printt ___ t__ *** reject















