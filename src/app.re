type action =
  | ReceiveRepos (array RepoData.repo);

type state = {repos: option (array RepoData.repo)};

let component = ReasonReact.reducerComponent "App";

let make _ => {
  ...component,
  initialState: fun () => ({repos: None}: state),
  reducer: fun action _state =>
    switch action {
    | ReceiveRepos repos => ReasonReact.Update {repos: Some repos}
    },
  didMount: fun {reduce} => {
    RepoData.fetchRepos () |>
    Js.Promise.then_ (
      fun repos => {
        reduce (fun _ => ReceiveRepos repos) ();
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
          Array.map (fun (repo: RepoData.repo) => <RepoItem key=repo.fullName repo />) repos
        )
      | None => ReasonReact.stringToElement "Loading"
      };
    Js.log repoItem;
    <div className="App">
      <div className="App-header">
        <h1> (ReasonReact.stringToElement "Reason Projects") </h1>
      </div>
      repoItem
    </div>
  }
};
