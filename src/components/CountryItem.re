[@react.component]
let make = (~country: ReactSelect.t) => {
  let flagName = "fi fi-" ++ country.value;
  let handleClick = () => Js.log("Clicked on " ++ country.label);

  <div style=Styles.value onClick={_event => handleClick()}>
    <span className=flagName />
    {React.string(" " ++ country.label)}
  </div>;
};
