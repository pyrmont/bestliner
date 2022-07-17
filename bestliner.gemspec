# frozen_string_literal: true

require "./lib/bestliner/version"

Gem::Specification.new do |s|
  s.name          = "bestliner"
  s.summary       = "Ruby wrapper for bestline, a C library for reading user input"
  s.description   = <<~eof
    Bestliner is a Ruby wrapper around bestline, a C library for interactive
    pseudoteletypewriter command sessions using ANSI Standard X3.64 control
    sequences. Bestliner supports Emacs-style editing shortcuts, a searchable
    history, completion and hint support via callbacks and UTF-8 editing.
  eof
  s.version       = Bestliner::VERSION
  s.author        = "Michael Camilleri"
  s.email         = "mike@inqk.net"
  s.homepage      = "https://github.com/pyrmont/bestliner"
  s.files         = `git ls-files`.strip.split(/\s+/).reject {|f| f.match(%r{^test/}) }
  s.require_paths = ["lib"]
  s.license       = "BSD-2"

  s.add_development_dependency "rake-compiler"
  s.add_development_dependency "yard"
end
