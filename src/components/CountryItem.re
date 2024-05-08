open ReactSelect;

module CountryItem = {
  [@react.component]
  let make =
      (
        ~country: ReactSelect.t,
        ~selectOption: option(ReactSelect.t => unit)=?,
      ) => {
    let flagName = "fi fi-" ++ country.value;

    let handleClick = _event => {
      Js.log(
        "Selected country: " ++ country.label ++ " (" ++ country.value ++ ")",
      );
      switch (selectOption) {
      | Some(selectOption) => selectOption(country)
      | None => ()
      };
    };

    <div style=Styles.value onClick={_event => handleClick(country)}>
      <span className=flagName />
      {React.string(" " ++ country.label)}
    </div>;
  };
};
