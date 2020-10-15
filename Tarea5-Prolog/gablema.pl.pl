camino(s,c,1).
camino(c,f,8).
camino(c,i,1).
camino(s,g,4).
camino(g,i,1).
camino(i,f,5).
camino(i,e,2).
camino(g,d,13).
camino(d,j,7).
camino(j,e,1).
camino(f,e,2).

path(X,Y,Lista) :- path(X,Y,Lista,[X]).
path(X,Y,Lista,_) :- camino(X,Y,Lista).
path(X,Y,Lista,L) :- %funcion para guardar los costos (en una lista) de los distintos caminos entre dos nodos
    camino(X,Z,C),
    not(member(Z,L)),
    append([Z],L,Ltemp),
    path(Z,Y,Cost,Ltemp),
    Lista is C+Cost.

todo_camino(X,Y,L) :-
    todo_camino(X,Y,[],L), !.

todo_camino(X,Y,Temp,L) :-
    path(X,Y,P),
    not(member(P,Temp)),
    append([P],Temp,Templ),
    todo_camino(X,Y,Templ,L).

todo_camino(_,_,Temp,Temp).

que_sumo(V,M,Health,[Ca|Co]) :-  %si la cabeza de la lista es menor o igual a la vida, se suma uno al contador de V
    Ca =< Health,
    que_sumo(V1,M,Health,Co),
    V is V1+1.
que_sumo(V,M,Health,[Ca|Co]):- %si la cabeza de la lista es mayor a la vida, se sumo uno al contador M de muertes
    Ca > Health,
    que_sumo(V,M1,Health, Co),
    M is M1+1.
que_sumo(0,0,_,[]).

suenoPeligroso(Health,V,M,X,Y):-
    todo_camino(X,Y,L),  %Guardo en una lista todos los largos de los caminos posibles
    que_sumo(V,M,Health,L). %calculo los valores de M y V.

