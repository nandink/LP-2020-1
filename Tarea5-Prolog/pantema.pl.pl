split_at(N, List, [H|[T]]) :- append(H, T, List), length(H, N).

grupoAtaque([], [], []).


grupoAtaque([P|R], List, [A|B]) :-
    split_at(P, List, [A, Sobrante]),
    grupoAtaque(R,Sobrante, B).
