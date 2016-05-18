(*******************************************************


 EP3 de Conceitos de Linguagens de Programação.

 Obs. para executar digitar no interpretador de SML
 - use "ep3.sml";

 *******************************************************)

exception Indefinido

structure BB = Bool;
structure II = Int;
structure SS = String;

datatype Expression = VInt of int
    | VBool of bool
    | Id of string
    | AExp of Expression * string * Expression
    | BExp of Expression * string * Expression
    | If of string * Expression * Expression * Expression;

(* return the value, if any, bound to the name. *)
    fun lookup(Id v, []) = raise Indefinido
        | lookup (Id v, (Id p, exp)::lassoc) = 
        if (Id v)= (Id p) then exp
        else lookup (Id v, lassoc);

    fun eval (VInt n, env) = VInt n
        | eval (VBool n, env) = VBool n
        | eval (Id n, env) = eval (lookup (Id n, env), env)
        | eval (AExp (e1,"+", e2), env) = let
        val VInt r1 = eval (e1, env)
        val VInt r2 = eval (e2, env)
        in
            print(SS.concat(["Reducao: de ", II.toString(r1), " + ", II.toString(r2), " para ", II.toString(r1+r2), "\n"]));
            VInt (r1 + r2)
        end
        | eval (AExp (e1, "-", e2), env) = let
        val VInt r1 = eval (e1, env)
        val VInt r2 = eval (e2, env)
        in
            print(SS.concat(["Reducao: de ", II.toString(r1), " - ", II.toString(r2), " para ", II.toString(r1-r2), "\n"]));
            VInt (r1 - r2)
        end
        | eval (BExp (e1, "And", e2), env) = let
        val VBool v1 = eval(e1, env)
        val VBool v2 = eval(e2, env)
        in
            print(SS.concat(["Reducao: de ", BB.toString(v1), " and ", BB.toString(v2), " para ", BB.toString(v1 andalso v2), "\n"]));
            VBool (v1 andalso v2)
        end
        | eval (BExp (e1, "Or", e2), env) = let
        val VBool v1 = eval(e1, env)
        val VBool v2 = eval(e2, env)
        in
            print(SS.concat(["Reducao: de ", BB.toString(v1), " or ", BB.toString(v2), " para ", BB.toString(v1 orelse v2), "\n"]));
            VBool (v1 orelse v2)
        end
        | eval (BExp (e1, "==", e2), env) = let
        val VInt r1 = eval (e1, env)
        val VInt r2 = eval (e2, env)
        in
            print(SS.concat(["Reducao: de ", II.toString(r1), " == ", II.toString(r2), " para ", BB.toString(r1 = r2), "\n"]));
            VBool (r1 = r2)
        end
        | eval (If (s, exp1, exp2, exp3), env) = let
        val VBool v = eval (exp1, env)
        in
            if v 
            then let
            in
                print("Reducao: do if - true - executando a primeira expressao.\n");
                eval(exp2, env)
            end
            else let
            in
                print("Reducao: do if - false - executando a segunda expressao.\n");
                eval(exp3, env)
            end
        end;

    fun insert_param_apriori([], [], env) = env
        | insert_param_apriori(ids, args, env) = let
        val id2 = hd ids
        val arg2 = eval (hd args, env)
        in
            insert_param_apriori(tl ids, tl args, (id2, arg2)::env)
        end;

    fun insert_param_sobdemanda([], [], env) = env
        | insert_param_sobdemanda(ids, args, env) = let
        val id2 = hd ids
        val arg2 = hd args
        in
            insert_param_sobdemanda(tl ids, tl args, (id2, arg2)::env)
        end;

    fun apriori ((string, ids, exp), args) = let
        val env = insert_param_apriori(ids, args, [])
        in
            eval(exp, env)
        end;

    fun sobdemanda ((string, ids, exp), args) = let
        val env = insert_param_sobdemanda(ids, args, [])
        in
            eval(exp, env)
        end;

(*********************
 TESTES
 *********************)

    print("\n\nTeste: (2+5)+3\n");
    sobdemanda (("fun", [Id "x", Id "y"], AExp (Id "x", "+", Id "y")), [AExp (VInt 2, "+", VInt 5), VInt 3]);
    apriori (("fun", [Id "x", Id "y"], AExp (Id "x", "+", Id "y")), [AExp (VInt 2, "+", VInt 5), VInt 3]);

    print("\n Teste 2+3\n");
    sobdemanda (("fun", [Id "x", Id "y"], AExp (Id "x", "+", Id "y")), [VInt 2, VInt 3]);
    apriori (("fun", [Id "x", Id "y"], AExp (Id "x", "+", Id "y")), [VInt 2, VInt 3]);

    print("\nTeste (2+3)+10");
    sobdemanda (("fun", [Id "x", Id "y"], AExp (AExp (Id "x", "+", Id "y"),"+", VInt 10)), [VInt 2, VInt 3]);
    apriori (("fun", [Id "x", Id "y"], AExp (AExp (Id "x", "+", Id "y"),"+", VInt 10)), [VInt 2, VInt 3]);

    print("\nTeste false and true\n");
    sobdemanda (("fun", [Id "x", Id "y"], BExp (Id "x", "And", Id "y")), [VBool false, VBool true]);
    apriori (("fun", [Id "x", Id "y"], BExp (Id "x", "And", Id "y")), [VBool false, VBool true]);

    print("\nTeste false or true\n");
    sobdemanda (("fun", [Id "x", Id "y"], BExp (Id "x", "Or", Id "y")), [VBool false, VBool true]);
    apriori (("fun", [Id "x", Id "y"], BExp (Id "x", "Or", Id "y")), [VBool false, VBool true]);

    print("\nTeste 2 == 3\n");
    sobdemanda (("fun", [Id "x", Id "y"], BExp (Id "x", "==", Id "y")), [VInt 2, VInt 3]);
    apriori (("fun", [Id "x", Id "y"], BExp (Id "x", "==", Id "y")), [VInt 2, VInt 3]);

    print("\nTeste if (6 == 6) then 6+6 else 6-6\n");
    sobdemanda (("fun", [Id "x", Id "y"], If ( "if", BExp (Id "y", "==", Id "y"), AExp (Id "y", "+", Id "y"), AExp (Id "y", "-", Id "y"))), [AExp (VInt 1, "+", VInt 5), VInt 6]);
    apriori (("fun", [Id "x", Id "y"], If ( "if", BExp (Id "y", "==", Id "y"), AExp (Id "y", "+", Id "y"), AExp (Id "y", "-", Id "y"))), [AExp (VInt 1, "+", VInt 5), VInt 6]);
