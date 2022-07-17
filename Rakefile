require "bundler/gem_tasks"
require "rake/extensiontask"
require "yard"

Rake::ExtensionTask.new("bestliner") do |ext|
  ext.lib_dir = "lib/bestliner"
end

YARD::Rake::YardocTask.new do |task|
  task.files = ["lib/**/*.rb"]
end

task default: [:clean, :compile]
