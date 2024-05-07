let url = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";

let castCountry = (json: Js.Json.t): ReactSelect.t => {
  switch (json |> Js.Json.decodeObject) {
  | Some(country) =>
    let label =
      Js.Dict.get(country, "label")
      |> Belt.Option.getExn
      |> Js.Json.decodeString
      |> Belt.Option.getExn;
    let value =
      Js.Dict.get(country, "value")
      |> Belt.Option.getExn
      |> Js.Json.decodeString
      |> Belt.Option.getExn;

    {label, value};

  | None => {label: "Unknown", value: "unknown"} // need to handle this case
  };
};

[@react.component]
let make = () => {
  let (options, setOptions) = React.useState(() => [||]);

  React.useEffect0(() => {
    Js.Promise.(
      Fetch.fetch(url)
      |> then_(Fetch.Response.json)
      |> then_(json =>
           Js.Json.decodeArray(json)
           |> Belt.Option.getExn
           |> Js.Array.map(~f=item => castCountry(item))
           |> resolve
         )
      |> then_(items => {
           setOptions(_ => items);
           resolve();
         })
      |> ignore
    );

    Some(() => ());
  });

  let optionComponent = (option: ReactSelect.t) => {
    <CountryItem.make country=option />;
  };

  let singleValueComponent = (option: ReactSelect.t) => {
    <CountryItem.make country=option />;
  };

  let handleChange = (option: ReactSelect.t) => {
    Js.log(
      "Selected country: " ++ option.label ++ " (" ++ option.value ++ ")",
    );
  };
  <div style=Styles.root>
    <ReactSelect
      options
      onChange=(handleChange: ReactSelect.t => unit)
      components={
        "Option": optionComponent,
        "SingleValue": singleValueComponent,
      }
    />
  </div>;
};
