
; the finite set of states
#Q = {q0,q1,q2,q3,accept,reject,printt,printr,printu,printe,printf,printa,printl,prints,halt}

; the finite set of input symbols
#S = {a,b,c}

; the complete set of tape symbols
#G = {a,b,_,c,t,r,u,e,f,a,l,s}

; the start state
#q0 = q0

; the blank symbol
#B = _

; the set of final states
#F = {accept}

; the number of tapes
#N = 3

; the transition functions

q0 a__ _aa rrr q0
q0 b__ _bb rrr q0
q0 c__ _cc rrr q0
q0 ___ ___ lll q1 ;head 2 at end

q1 _aa _aa *l* q1
q1 _ab _ab *l* q1
q1 _ac _ac *l* q1
q1 _bb _bb *l* q1
q1 _ba _ba *l* q1
q1 _bc _bc *l* q1
q1 _cc _cc *l* q1
q1 _ca _ca *l* q1
q1 _cb _cb *l* q1
q1 __a __a *r* q2 ;head 1 at start
q1 __b __b *r* q2
q1 __c __c *r* q2

q2 _aa _aa *rl q2
q2 _bb _bb *rl q2
q2 _ab ___ *** reject
q2 _ba ___ *** reject
q2 _ac ___ *** reject
q2 _ca ___ *** reject
q2 _bc ___ *** reject
q2 _cb ___ *** reject
q2 _cc _cc *rl q3

q3 _aa _aa *rl q3
q3 _bb _bb *rl q3
q3 _cc ___ *** reject
q3 _ab ___ *** reject
q3 _ba ___ *** reject
q3 _ac ___ *** reject
q3 _ca ___ *** reject
q3 _bc ___ *** reject
q3 _cb ___ *** reject
q3 ___ ___ *** accept

accept ___ ___ *** printt
printt ___ t__ r** printr
printr ___ r__ r** printu
printu ___ u__ r** printe
printe ___ e__ *** halt

reject ___ ___ *** printf
printf ___ f__ r** printa
printa ___ a__ r** printl
printl ___ l__ r** prints 
prints ___ s__ r** printe




















