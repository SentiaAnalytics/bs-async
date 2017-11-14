let (>>) = (f, g, a) => g(f(a));

type result('err, 'ok) =
  | Error('err)
  | Ok('ok)
;

type async('a) = ('a => unit) => unit;

type promise('err, 'ok) = (result('err, 'ok) => unit) => unit;

module Result = {
  let map = (f, res) =>
    switch res {
    | Error(x) => Error(x)
    | Ok(a) => Ok(f(a))
    };
  
  let map2 = (f, r1, r2) =>
    switch (r1, r2) {
    | (Ok(a1), Ok(a2)) => Ok(f(a1, a2))
    | (Error(x), _) => Error(x)
    | (_, Error(x)) => Error(x)
    };
  
  let map3 = (f, r1, r2, r3) =>
    switch (r1, r2, r3) {
    | (Ok(a1), Ok(a2), Ok(a3)) => Ok(f(a1, a2, a3))
    | (Error(x), _, _) => Error(x)
    | (_, Error(x), _) => Error(x)
    | (_, _, Error(x)) => Error(x)
    };
  
  let flatten = (r) =>
    switch r {
    | Error(e) => Error(e)
    | Ok(a) => a
    };
  
  let flatMap = (f, res) =>
    switch res {
    | Error(x) => Error(x)
    | Ok(a) => f(a)
    };
  
  let withDefault = (a, res) =>
    switch res {
    | Error(_) => a
    | Ok(a) => a
    };
  
  let fromOption = (err, opt) =>
    switch opt {
    | None => Error(err)
    | Some(a) => Ok(a)
    };
  
  let isError = (res) =>
    switch res {
    | Error(_) => true
    | _ => false
    };
  
  let isOk = (res) =>
    switch res {
    | Ok(_) => true
    | _ => false
    };
  
  let encode = (encodeError, encodeOk) =>
    fun
    | Error(e) => encodeError(e)
    | Ok(v) => encodeOk(v);
};

module Async = {
  let none = (_) => ();
  let make = (a) => ((cb) => cb(a));
  let map = (f, a) => (cb) => a(f >> cb);
  let flatten = (a) => (cb) => a((b) => b(cb));
  let flatMap = (f, a) => flatten @@ map(f, a);
};

module Promise = {
  let none = (_) => ();
  let resolve = (a) => ((cb) => cb(Ok(a)));
  let reject = (x) => ((cb) => cb(Error(x)));
  let map = (f, a) => (cb) => a((x) => switch x {
    | Error(err) => cb @@ Error(err)
    | Ok(value) => cb @@ Ok(f(value))
  });
  
  let flatten = (a) => (cb) => a((res) => switch res {
    | Error(err) => cb @@ Error(err)
    | Ok(a) => a((res) => switch res {
      | Error(err) => cb @@ Error(err)
      | Ok(value) => cb @@ Ok(value)
    });
  });
  let flatMap = (f, a) => (cb) => a((res) => switch res {
    | Error(err) => cb @@ Error(err)
    | Ok(value) => f(value, (res) => switch res {
      | Error(err) => cb @@ Error(err)
      | Ok(value) => cb @@ Ok(value)
    });
  });

  let catch = (f, a) => (cb) => a((x) => switch x {
    | Error(err) => cb @@ Ok(f(err))
    | Ok(value) => cb @@ Ok(value)
  });

  let flatCatch = (f, a) => (cb) => a((res) => switch res {
    | Ok(value) => cb @@ Ok(value)
    | Error(err) => f(err, (res) => switch res {
      | Error(err) => cb @@ Error(err)
      | Ok(value) => cb @@ Ok(value)
    });
  });

  let fromOption = (default, opt) => switch opt {
    | None => reject(default)
    | Some(a) => resolve(a)
  };
  let fromResult = (res) => (cb) => cb(res);

};





