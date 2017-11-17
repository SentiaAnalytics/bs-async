type result('err, 'ok) = Js.Result.t('err, 'ok);

type async('a) = ('a => unit) => unit;
let none : async('a);
let make : 'a => async('a);
let map : ('a => 'b) => async('a) => async('b);
let flatten: async(async('a)) => async('a);
let flatMap : ('a => async('b)) => async('a) => async('b);