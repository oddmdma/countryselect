module ReactSelect = {
  type t = {
    label: string,
    value: string,
  };

  type componentProps = {
    data: t,
    selectOption: option(t => unit),
  };

  type components = {
    .
    "Option": Js.Nullable.t(componentProps => React.element),
    // "SingleValue": Js.Nullable.t(componentProps => React.element),
  };

  [@mel.module "react-select"] [@react.component]
  external make:
    (~options: array(t), ~onChange: t => unit, ~components: components) =>
    React.element =
    "default";
};
