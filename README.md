# Bestliner

[![Gem Version][gem-badge]][gem-link]

[gem-badge]: https://badge.fury.io/rb/bestliner.svg
[gem-link]: https://rubygems.org/gems/bestliner

Bestliner is a Ruby wrapper around the [bestline library][bestline] by Justine
Tunney. The bestline library is written in portable ANSI C99 and provides
interactive pseudoteletypewriter command sessions using ANSI Standard X3.64
control sequences.

Bestliner supports Emacs-style editing shortcuts, a searchable history,
completion and hint support via callbacks and UTF-8 editing.

[bestline]: https://github.com/jart/bestline

## Example

Here's a prompt that echos the input back to the user:

```ruby
require "bestliner"

while line = Bestliner.bestline("> ") do
  puts line
end
```

The prompt includes Emacs-style shortcuts, a searchable history and UTF-8
editing all out of the box courtesy of the wrapped bestline library.

## Installation

Bestliner is available as a gem:

```shell
$ gem install bestliner
```

## Documentation

More information is available in the [docs][].

[docs]: https://rubydoc.info/github/pyrmont/bestliner

## Bugs

Found a bug? I'd love to know about it. The best way is to report it in the
[Issues section][ghi] on GitHub.

[ghi]: https://github.com/pyrmont/bestliner/issues

## Versioning

Bestliner uses [Semantic Versioning 2.0.0][sv2].

[sv2]: http://semver.org/

## Licence

Bestliner is licensed under the BSD-2 licence.  See [LICENSE][] for more
details.

[LICENSE]: https://github.com/pyrmont/bestliner/blob/master/LICENSE
