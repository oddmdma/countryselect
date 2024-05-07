type t = {
  label: string,
  value: string,
};

[@mel.module "react-select"]
external reactSelect:
  React.component({
    .
    "options": array(t),
    "onChange": t => unit,
    "components": Js.t({..}),
  }) =
  "default";

[@mel.module "react-select"]
[@react.component]
let make =
    (~options: array(t), ~onChange: t => unit, ~components: Js.t({..})) => {
  React.createElement(
    reactSelect,
    {"options": options, "onChange": onChange, "components": components},
  );
};
