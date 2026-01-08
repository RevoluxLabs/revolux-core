# Contributing to Revolux-Core

Thank you for your interest in contributing to Revolux-Core.

Revolux-Core is an independent Layer-1 blockchain implementation focused on fair launch, strong default privacy, and protocol-level auditability. Contributions of all kinds are welcome, including testing, documentation improvements, and code changes.

A good way to help is to test the software and report bugs. See *How to Report Bugs Effectively* (by Simon Tatham) for guidance on writing useful bug reports.

---

## General Guidelines

- Comments are encouraged.
- If modifying code for which Doxygen headers exist, the headers must be updated accordingly.
- Tests are encouraged when adding new functionality.
- Patches should be submitted via GitHub Pull Requests.
- Patches must be self-contained. One logical change per patch.
- Avoid unrelated whitespace, formatting, or spelling changes unless user-visible.
- Follow the existing code style in the modified area.
- Use `git add -p` to stage only relevant changes.

---

## Commits and Pull Requests

- Commit messages should be clear and descriptive.
- Use the following subject line format:

- Pull requests should be rebased (no merge commits).
- Maintainers may request rebasing or clarification.
- PGP signing commits is strongly encouraged.

---

## Code of Conduct (C4 / RFC 2119)

The key words **MUST**, **MUST NOT**, **REQUIRED**, **SHALL**, **SHALL NOT**, **SHOULD**, **SHOULD NOT**, **RECOMMENDED**, **MAY**, and **OPTIONAL** in this document are to be interpreted as described in RFC 2119.

---

## Licensing and Ownership

- Revolux-Core is licensed under the GNU General Public License v3 or later.
- All contributions must use the same license.
- Contributors retain copyright to their contributions.
- There is no copyright assignment requirement.

---

## Patch Requirements

- Patches MUST compile cleanly and pass existing tests on the primary target platform.
- Patches MUST NOT include non-trivial code from other projects unless the contributor is the original author.
- A patch SHOULD address exactly one clearly defined issue.
- A patch MUST adhere to documented public contracts and protocol rules.

---

## Development Process

- Changes MUST be driven by clearly identified problems.
- To propose a change, open an issue on GitHub describing the problem.
- Consensus SHOULD be reached before major changes.
- Contributors MUST work on forks and submit pull requests.
- Patches MUST NOT be committed directly to the main repository.

---

## Evolution of Public Contracts

- All public APIs and protocol rules MUST be documented.
- Backward compatibility SHOULD be preserved unless there is explicit consensus.
- New features MUST use new identifiers.
- Deprecated features SHOULD follow a clear deprecation lifecycle.
- Removed features MUST fail explicitly if used.

---

## Project Administration

- The **Revolux Core Maintainers** act as Administrators of this repository.
- Administrators are responsible for:
  - Managing Maintainers
  - Enforcing contribution and governance rules
  - Ensuring continuity of stewardship

- Administrators MAY remove inactive Maintainers or those who repeatedly violate project rules.
- Administrators MAY block or ban bad actors after public discussion and review.
- Maintainers MUST NOT merge changes to governance documents without administrator approval.

---

## Scope of Contributions

- Contributions MUST relate directly to Revolux-Core, its documented roadmap, or its dependencies.
- Feature requests unrelated to Revolux-Core SHOULD NOT be submitted.

---

Thank you for helping build Revolux-Core.

