type result('err, 'ok) =
  | Error('err)
  | Ok('ok)
;

type async('a) = ('a => unit) => unit;
type promise('err, 'ok) = (result('err, 'ok) => unit) => unit;

module Result : {
    let map: ('a => 'b, result('x, 'a)) => result('x, 'b);
    let map2: (('a, 'b) => 'c, result('x, 'a), result('x, 'b)) => result('x, 'c);
    let map3: (('a, 'b, 'c) => 'd, result('x, 'a), result('x, 'b), result('x, 'c)) => result('x, 'd);
    let flatten: result('x, result('x, 'a)) => result('x, 'a);
    let flatMap: ('a => result('x, 'b), result('x, 'a)) => result('x, 'b);
    let withDefault: ('a, result('x, 'a)) => 'a;
    let fromOption: ('x, option('a)) => result('x, 'a);
    let isError: result('x, 'a) => bool;
    let isOk: result('x, 'a) => bool;
    let encode: ('x => Js.Json.t, 'a => Js.Json.t, result('x, 'a)) => Js.Json.t;
};

module Async : {
    let none : async('a);
    let make : 'a => async('a);
    let map : ('a => 'b) => async('a) => async('b);
    let flatten: async(async('a)) => async('a);
    let flatMap : ('a => async('b)) => async('a) => async('b);
};


module Promise : {
    let none : promise('x, 'a);
    let resolve : 'a => promise('x, 'a);
    let reject : 'x => promise('x, 'a);
    let map : ('a => 'b) => promise('err, 'a) => promise('err, 'b);
    let flatten: promise('x, promise('x, 'a)) => promise('x, 'a);
    let flatMap : ('a => promise('err, 'b)) => promise('err, 'a) => promise('err, 'b);
    let catch : ('err => 'a) => promise('err, 'a) => promise(unit, 'a);
    let flatCatch : ('x => promise('y, 'a)) => promise('x, 'a) => promise('y, 'a);
    let fromOption: ('x, option('a)) => promise('x, 'a);
    let fromResult: result('x, 'a) => promise('x, 'a);
};