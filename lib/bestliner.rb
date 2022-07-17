# frozen_string_literal: true

module Bestliner
  class << self
    # Reads text input after an optional prompt
    #
    # @param prompt [String] the prompt to display before the input cursor
    # @return [String, nil] the line of input, `nil` if EOF
    def bestline(prompt = "")
      raise ArgumentError, "prompt must be of class String" unless prompt.is_a?(String)
      __bestline prompt
    end

    # Reads text input after an optional prompt and saves input to a file
    #
    # @param prompt [String] the prompt to display before the input cursor
    # @param filename [String] the file to use for saving input history
    # @return (see #bestline)
    def bestline_with_history(prompt = "", filename = ".bestliner_history")
      raise ArgumentError, "prompt must be of class String" unless prompt.is_a?(String)
      raise ArgumentError, "filename must be of class String" unless filename.is_a?(String)
      __bestline_with_history prompt, filename
    end

    # Reads text input after an optional prompt from the input and displays on output
    #
    # @param prompt [String] the prompt to display before the input cursor
    # @param input [IO] the stream to use as input
    # @param output [IO] the stream to use as output
    # @return (see #bestline)
    def bestline_raw(prompt = "", input, output)
      raise ArgumentError, "prompt must be of class String" unless prompt.is_a?(String)
      raise ArgumentError, "input must be of class IO" unless input.is_a?(IO)
      raise ArgumentError, "output must be of class IO" unless output.is_a?(IO)
      __bestline_raw prompt, input.fileno, output.fileno
    end

    # Adds the line to the internal history
    #
    # @param line [String] the line to add
    def add_history(line)
      raise ArgumentError, "line must be of class String" unless line.is_a?(String)
      return_code = __add_history line
      raise IOError, "cannot write to history" unless return_code == 1
    end

    # Saves the history to the file
    #
    # @param filename [String] the filename to use
    def save_history(filename)
      raise ArgumentError, "filename must be of class String" unless filename.is_a?(String)
      return_code = __save_history filename
      raise IOError, "cannot save history to #{filename}" unless return_code == 0
    end

    # Loads the history from the file
    #
    # @param (see #save_history)
    def load_history(filename)
      raise Errno::ENOENT, filename unless File.exist?(filename)
      return_code = __load_history filename
      raise IOError, "cannot load history from #{filename}" unless return_code == 0
    end

    # Frees the memory used for the internal history
    def free_history
      __free_history
    end

    # Clears the screen of the output stream
    #
    # @param output [IO] the stream to use as output
    def clear_screen(output)
      raise ArgumentError, "output must be of class IO" unless output.is_a?(IO)
      __clear_screen output.fileno
    end

    # Sets the mask mode
    #
    # @param is_enabled [Boolean] whether mask mode is enabled
    def mask_mode=(is_enabled)
      @mask_mode = if is_enabled
        __mask_mode_enable
      else
        __mask_mode_disable
      end
    end

    # Checks the status of mask mode
    #
    # @return [Boolean] whether mask mode is enabled
    def mask_mode?
      !!(defined?(@mask_mode) && @mask_mode)
    end

    # Sets the completion callback
    #
    # @param callback [#call] callback that returns completions
    def completion_callback=(callback)
      raise ArgumentError, "callback must respond to :call" unless callback.respond_to?(:call)
      __set_completion_cb callback
    end

    # Sets the hints callback
    #
    # @param callback [#call] callback that returns a hint
    def hints_callback=(callback)
      raise ArgumentError, "callback must respond to :call" unless callback.respond_to?(:call)
      __set_hints_cb callback
    end


    # Sets the ANSI code to use before a hint
    #
    # @param ansi_code [String] ANSI code output before hint
    def hints_before=(ansi_code)
      raise ArgumentError, "ansi_code must be of class String" unless ansi_code.is_a?(String)
      @hints_before = ansi_code
    end

    # Sets the ANSI code to use after a hint
    #
    # @param ansi_code [String] ANSI code output after hint
    def hints_after=(ansi_code)
      raise ArgumentError, "ansi_code must be of class String" unless ansi_code.is_a?(String)
      @hints_after = ansi_code
    end
  end
end

require "bestliner/bestliner"
