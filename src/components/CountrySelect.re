open ReactSelect;
open CountryItem;
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
  // let (selectedOption, setSelectedOption) =
  // React.useState(() => Js.Nullable.return(options->Belt.Array.get(0)));

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

  let countryComponent = (props: ReactSelect.componentProps) => {
    let data = props.data;
    let selectOption = props.selectOption;

    switch (selectOption) {
    | Some(func) => <CountryItem.make country=data selectOption=func />
    | None => <CountryItem.make country=data />
    };
  };

  let handleChange = (option: ReactSelect.t) => {
    Js.log(
      "Selected country: " ++ option.label ++ " (" ++ option.value ++ ")",
    );
  };
  <div style=Styles.root>
    <ReactSelect
      options
      onChange=handleChange
      components={
        "Option": Js.Nullable.return(countryComponent),
        // "SingleValue": Js.Nullable.return(countryComponent),
      }
    />
  </div>;
};
