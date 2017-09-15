type action =
  | FetchRepos (array RepoData.repo);

type state = {repos: option (array RepoData.repo)};

let component = ReasonReact.reducerComponent "App";

let dummyRepos: array RepoData.repo = [|
  RepoData.parseRepoJson (
    Js.Json.parseExn {js|
 		{
 		   "full_name": "reasonml/reason-tools",
 		   "stargazers_count": 93,
 		   "html_url": "https://github.com/reasonml/reason-tools"
 		}
	|js}
  )
|];

let make _ => {
  ...component,
  initialState: fun () => ({repos: Some dummyRepos}: state),
  reducer: fun action _ =>
    switch action {
    | FetchRepos repos => ReasonReact.Update {repos: Some repos}
    },
  didMount: fun {reduce} => {
    RepoData.fetchRepos () |>
    Js.Promise.then_ (
      fun repos => {
        reduce (fun _ => FetchRepos repos) ();
        Js.Promise.resolve ()
      }
    ) |> ignore;
    ReasonReact.NoUpdate
  },
  render: fun {state} => {
    let repoItem =
      switch state.repos {
      | Some repos =>
        ReasonReact.arrayToElement (
          Array.map (fun (repo: RepoData.repo) => <RepoItem key=repo.full_name repo />) repos
        )
      | None => ReasonReact.stringToElement "Loading"
      };
    <div className="App">
      <div className="App-header">
        <h1> (ReasonReact.stringToElement "Reason Projects") </h1>
      </div>
      repoItem
    </div>
  }
};
