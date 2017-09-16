open Bs_fetch;

let reposUrl = "https://api.github.com/search/repositories?q=topic%3Areasonml&type=Repositories";

type repo = {
  fullName: string,
  stargazersCount: int,
  htmlUrl: string,
  description: option string
};

let parseRepoJson json :repo =>
  Json.Decode.{
    fullName: json |> field "full_name" string,
    stargazersCount: json |> field "stargazers_count" int,
    htmlUrl: json |> field "html_url" string,
    description: json |> optional (field "description" string)
  };

let parseReposResponseJson json :array repo =>
  Json.Decode.(json |> field "items" (array parseRepoJson));

let fetchRepos () =>
  Js.Promise.(
    fetch reposUrl |> then_ Response.json |>
    then_ (fun text => parseReposResponseJson text |> resolve)
  );
