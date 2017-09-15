open Bs_fetch;

let reposUrl = "https://api.github.com/search/repositories?q=topic%3Areasonml&type=Repositories";

type repo = {
  full_name: string,
  stargazers_count: int,
  html_url: string
};

let parseRepoJson json :repo =>
  Json.Decode.{
    full_name: field "full_name" string json,
    stargazers_count: field "stargazers_count" int json,
    html_url: field "html_url" string json
  };

let parseReposResponseJson json =>
  Json.Decode.field "items" (Json.Decode.array parseRepoJson) json;

let fetchRepos () =>
  Js.Promise.(
    fetch reposUrl |> then_ Response.json |>
    then_ (fun text => parseReposResponseJson text |> resolve)
  );
