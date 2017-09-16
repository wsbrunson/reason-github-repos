let component = ReasonReact.statelessComponent "RepoItem";

let make repo::({htmlUrl, fullName, description, stargazersCount}: RepoData.repo) _ => {
  ...component,
  render: fun _ =>
    <div className="RepoItem">
      <a className="RepoItem-url" href=htmlUrl>
        <h2> (ReasonReact.stringToElement fullName) </h2>
      </a>
      <p className="RepoItem-desc">
        (
          switch description {
          | Some desc => ReasonReact.stringToElement desc
          | None => ReasonReact.stringToElement ""
          }
        )
      </p>
      <span className="RepoItem-stars">
        (ReasonReact.stringToElement (string_of_int stargazersCount ^ " stars"))
      </span>
    </div>
};
