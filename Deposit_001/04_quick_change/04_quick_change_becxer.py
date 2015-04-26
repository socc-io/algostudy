money = int(raw_input())
res = ''
res += str(money / 25) + ' QUARTER(S), '
money = money % 25
res += str(money / 10) + ' DIME(S), '
money = money % 10
res += str(money / 5) + ' NICKEL(S), '
money = money % 5 
res += str(money / 1) + ' PENNY(S)'
print res 
