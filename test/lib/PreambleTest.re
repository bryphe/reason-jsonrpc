open TestFramework;

module Preamble = Reason_jsonrpc.Preamble;

describe("Preamble", ({test, describe, _}) => {
  test("hasContentLengthHeader", ({expect, _}) => {
    expect.bool(Preamble.hasContentLengthHeader("Content-Length: 100")).toBe(
      true,
    );
    expect.bool(Preamble.hasContentLengthHeader("Content-Length:")).toBe(
      false,
    );
    expect.bool(Preamble.hasContentLengthHeader("\r\n")).toBe(false);
    expect.bool(Preamble.hasContentLengthHeader("")).toBe(false);
  });

  describe("getContentLength", ({test, _}) =>
    test("basic case", ({expect, _}) => {
      let length = Preamble.getContentLength("Content-Length: 128\r\n");
      expect.int(length).toBe(128);
    })
  );
  describe("parseLine", ({test, _}) => {
    test("content-length case", ({expect, _}) => {
      let v = Preamble.parseLine("Content-Length: 1028\r\n");
      expect.int(v.contentLength).toBe(1028);
      expect.bool(v.isComplete).toBe(false);
    });

    test("completes with empty line", ({expect, _}) => {
      let v = Preamble.parseLine("Content-Length: 1028\r\n");
      let v = Preamble.parseLine(~current=v, "\r\n");
      expect.bool(v.isComplete).toBe(true);
    });

    test("ignores other headers for now", ({expect, _}) => {
      let v = Preamble.parseLine("Content-Length: 1\r\n");
      let v = Preamble.parseLine(~current=v, "Content-Type: some type\r\n");
      let v =
        Preamble.parseLine(~current=v, "A-Random-Header: some type\r\n");
      let v = Preamble.parseLine(~current=v, "\r\n");
      expect.int(v.contentLength).toBe(1);
      expect.bool(v.isComplete).toBe(true);
    });
  });
});
