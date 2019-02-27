/* Utility methods for working with Yojson */

let hasField = (f: string, msg: Yojson.Safe.json) => {
  let v = Yojson.Safe.Util.member(f, msg);

  switch (v) {
  | `Null => false
  | _ => true
  };
};

exception ParseException(string);

let hasMethod = hasField("method");
let hasId = hasField("id");
let hasResult = hasField("result");
