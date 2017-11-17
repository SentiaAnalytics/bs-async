let (>>) = (f, g, a) => g(f(a));

type result('err, 'ok) = Js.Result.t('err, 'ok);

type async('a) = ('a => unit) => unit;

let none = (_) => ();
let make = (a) => ((cb) => cb(a));
let map = (f, a) => (cb) => a(f >> cb);
let flatten = (a) => (cb) => a((b) => b(cb));
let flatMap = (f, a) => flatten @@ map(f, a);