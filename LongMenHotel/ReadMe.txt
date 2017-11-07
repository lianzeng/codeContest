I have implement 3 ways for this problem, all output path:
1.back-trace, DFS.                           refer to: SearchPath.cpp/hpp;
2.Dijkstra to caculate shortest distance.    refer to: Dijkstra.cpp/hpp;
3.greedy BFS to caculate shortest distance.  refer to: GreedyBFS.cpp/hpp;


龙门客栈
明朝宪宗年间，宦官弄权，滥杀贤臣。侠客赵怀安在营救忠良行动中，将恶贯满盈的东厂督主万喻楼一剑毙命，引来西厂督主雨化田，祭出天下格杀令。
赵怀安等人一路亡命，途中布满了西厂的眼线，一旦被发现他们将面临全天下亡命之徒的围攻。 他们得知曾毁于大火的龙门客栈里，风骚的老板娘早已神秘失踪，只剩下逃过火劫的伙计们重起炉灶，痴等老板娘回来。
于是他们决定前往龙门客栈寻求帮忙。但铺天盖地的黑沙暴即将来临，好在他们得到了西厂的布防图。
但布防图太复杂，一时也判断不出是否能在规定的时间内到达龙门客栈。 关键时刻赵怀安使出了“一梦千年”的绝技，托梦给500年后的你，现在请你帮忙计算出来他们在规定的时间内能否有机会到达龙门客栈？
他会为你提供西厂的布防图以及黑沙暴到来的时间T。请你用现代科技帮忙判断是否能在规定的时间内到达龙门客栈。

Input
题目包括多组测试数据。
每组测试数据以三个整数N,M,T(0 < N,M <= 20)开头，
分别代表布防图的列(N)和行(M)，以黑沙暴到来的天数(T)。
紧接着有M行，N列字符，由”.”，”*”，”Z”，”L”组成。每行中每两个字符用空格隔开。其中
“.” 代表能够通过的道路。
“*” 代表有西厂的眼线，赵怀安不能从此通过，可视为障碍。
“L” 是龙六客栈所在的位置，终点。
“Z” 是赵怀安的起始位置，起点。
每天赵怀安只能选择上、下、左、右任意一方向走一条路。

Output
输出格式 Case #caseIndex: result
caseIndex是case序号，从 1 开始。
restult 是 "YES" 或 "NO" 如果能在规定时间内到达龙门客栈，则是”YES", 否则是”NO“

例子
Input
2
4 4 5
. . . L
. * . .
. * . .
Z . . *
3 4 5
. . L
* . .
* . .
Z . *

Output
Case #1: NO
Case #2: YES
