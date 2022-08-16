// slang-artifact-associated.h
#ifndef SLANG_ARTIFACT_ASSOCIATED_H
#define SLANG_ARTIFACT_ASSOCIATED_H

#include "slang-artifact.h"

namespace Slang
{

/* Diagnostics.

If there are raw diagnostics they can be associated to an artifact as (Kind::Text, Payload::Diagnostics) artifact */
class IDiagnostics : public ICastable
{
public:
    SLANG_COM_INTERFACE(0x91f9b857, 0xcd6b, 0x45ca, { 0x8e, 0x3, 0x8f, 0xa3, 0x3c, 0x5c, 0xf0, 0x1a });

    enum class Severity
    {
        Unknown,
        Info,
        Warning,
        Error,
        CountOf,
    };
    enum class Stage
    {
        Compile,
        Link,
    };

    struct Location
    {
        Int line = 0;                   ///< One indexed line number. 0 if not defined
        Int column = 0;                 ///< One indexed *character (not byte)* column number. 0 if not defined
    };

    struct Diagnostic
    {
        Severity severity = Severity::Unknown;          ///< The severity of error
        Stage stage = Stage::Compile;                   ///< The stage the error came from
        ZeroTerminatedCharSlice text;                   ///< The text of the error
        ZeroTerminatedCharSlice code;                   ///< The compiler specific error code
        ZeroTerminatedCharSlice filePath;               ///< The path the error originated from
        Location location;
    };

        /// Get the diagnostic at the index
    SLANG_NO_THROW virtual const Diagnostic* SLANG_MCALL getAt(Index i) = 0;
        /// Get the amount of diangostics
    SLANG_NO_THROW virtual Count SLANG_MCALL getCount() = 0;
        /// Add a diagnostic
    SLANG_NO_THROW virtual void SLANG_MCALL add(const Diagnostic& diagnostic) = 0;
        /// Remove the diagnostic at the index
    SLANG_NO_THROW virtual void SLANG_MCALL removeAt(Index i) = 0;

        /// Get raw diagnostics information
    SLANG_NO_THROW virtual ZeroTerminatedCharSlice SLANG_MCALL getRaw() = 0;
        /// Set the raw diagnostic info
    SLANG_NO_THROW virtual void SLANG_MCALL setRaw(const ZeroTerminatedCharSlice& slice) = 0;

        /// Get the result for a compilation
    SLANG_NO_THROW virtual SlangResult SLANG_MCALL getResult() = 0;
        /// Set the result
    SLANG_NO_THROW virtual void SLANG_MCALL setResult(SlangResult res) = 0;

        /// Reset all state
    SLANG_NO_THROW virtual void SLANG_MCALL reset() = 0;

        /// Count the number of diagnostics which have 'severity' or greater 
    SLANG_NO_THROW virtual Count SLANG_MCALL getCountAtLeastSeverity(Severity severity) = 0;

        /// Get the number of diagnostics by severity
    SLANG_NO_THROW virtual Count SLANG_MCALL getCountBySeverity(Severity severity) = 0;

        /// True if there are any diagnostics of severity or worse
    SLANG_NO_THROW virtual bool SLANG_MCALL hasOfAtLeastSeverity(Severity severity) = 0;

        /// Stores in outCounts, the amount of diagnostics for the stage of each severity
    SLANG_NO_THROW virtual Count SLANG_MCALL getCountByStage(Stage stage, Count outCounts[Int(Severity::CountOf)]) = 0;

        /// Remove all diagnostics of the type
    SLANG_NO_THROW virtual void SLANG_MCALL removeBySeverity(Severity severity) = 0;

        /// Add a note
    SLANG_NO_THROW virtual void SLANG_MCALL maybeAddNote(const ZeroTerminatedCharSlice& in) = 0;

        /// If there are no error diagnostics, adds a generic error diagnostic
    SLANG_NO_THROW virtual void SLANG_MCALL requireErrorDiagnostic() = 0;

        /// Append a summary to out
    SLANG_NO_THROW virtual void SLANG_MCALL appendSummary(ISlangBlob** outBlob) = 0;
        /// Appends a summary that just identifies if there is an error of a type (not a count)
    SLANG_NO_THROW virtual void SLANG_MCALL appendSimplifiedSummary(ISlangBlob** outBlob) = 0;
};

struct ShaderBindingRange;

class IPostEmitMetadata : public ICastable
{
public:
    SLANG_COM_INTERFACE(0x5d03bce9, 0xafb1, 0x4fc8, { 0xa4, 0x6f, 0x3c, 0xe0, 0x7b, 0x6, 0x1b, 0x1b });

        /// Get the binding ranges
    SLANG_NO_THROW virtual Slice<ShaderBindingRange> SLANG_MCALL getUsedBindingRanges() = 0;
};

} // namespace Slang

#endif
