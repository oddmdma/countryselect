[@mel.deriving abstract]
type selectOption = {
  label: string,
  value: string,
};

[@mel.module "react-select"]
external reactSelect:
  React.component({
    .
    "options": array(selectOption),
    "onChange": selectOption => unit,
  }) =
  "default";

[@react.component]
let make = (~options: array(selectOption), ~onChange: selectOption => unit) =>
  React.createElement(
    reactSelect,
    {"options": options, "onChange": onChange},
  );
