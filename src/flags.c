#include <stdint.h>

#include "flags.h"
#include "util.h"

struct opt_config *load_compress_args(){
    struct opt_config *conf = opt_config_init();
    int32_t cpus = num_cpus();

    opt_flag_int(conf, 
        &compress_flags.gapped_window_size, "gapped-window-size", 100,
        "The size of the gapped match window.");
    opt_flag_int(conf,
        &compress_flags.procs, "procs", cpus,
        "The number of total CPUs to use to divide work.");
    opt_flag_int(conf,
        &compress_flags.map_seed_size, "map-seed-size", 10,
        "The size of a seed in the k-mer map.  Must be less than 16.");
    opt_flag_int(conf,
        &compress_flags.ext_seq_id_threshold, "ext-seq-id-threshold", 50,
        "The sequence identity threshold of [un]gapped extension.");
    opt_flag_int(conf,
        &compress_flags.min_match_len, "min-match-len", 300,
        "The minimum size of an extension needed for a match to be recorded.");
    opt_flag_int(conf,
        &compress_flags.max_kmer_freq, "max-kmer-freq", 500,
        "The maximum number of entries for a k-mer in the seeds table.");
    opt_flag_int(conf,
        &compress_flags.overlap, "overlap", 100,
        "The number of bases to backtrack by when starting a new chunk during "
        "compression and the number of bases to include in the chunk of DNA "
        "before a match.");
    opt_flag_int(conf,
        &compress_flags.max_chunk_size, "max-chunk-size", 10000,
        "The maximum number of bases that are checked before adding a "
        "chunk without a match.");
    opt_flag_int(conf,
        &compress_flags.min_progress, "min-progress", 50,
        "The minimum progress that needs to be made in each direction of "
        "attempt_ext to consider a seed as a potential match.");
    opt_flag_int(conf,
        &compress_flags.consec_match_clump_size, "consec-match-clump-size", 4,
        "The number of consecutive matches needed to check for a bad window in "
        "align_ungapped.");
    opt_flag_int(conf,
        &compress_flags.window_ident_thresh, "window-ident-thresh", 85,
        "The minimum number of matches that must be in the array of matches "
        "for the current window not to be considered a bad window.");
    opt_flag_int(conf,
        &compress_flags.btwn_match_min_dist_check, 
        "btwn-match-min-dist-check", 10,
        "The number of bases scanned since the last clump of matches in "
        "align_ungapped that results in checking for 50%% identity since the "
        "last clump.");
    opt_flag_int(conf,
        &compress_flags.notify_every, "notify-every", 1000,
        "Sets how many sequences to compress for each notification of how many "
        "sequences have been compressed so far.  Pass in 0 to disable "
        "notifications entirely.");
    opt_flag_int(conf,
        &compress_flags.max_consec_mismatch, "max-consec-mismatch", 3,
        "The number of consecutive mismatches to find before exiting "
        "attempt_ext.");

    return conf;
}

struct opt_config *load_search_args(){
    struct opt_config *conf = opt_config_init();

    opt_flag_string(conf,
        &search_flags.coarse_evalue, "coarse-evalue", "1e-20",
        "The e-value used during coarse search.  To set the e-value for fine "
        "search, add it as an argument in --blast-args, which is the list of "
        "arguments to pass into BLAST during fine search.");
    opt_flag_bool(conf,
        &search_flags.no_cleanup, "no-cleanup",
        "Pass this flag to keep the coarse search results XML file.");
    opt_flag_bool(conf,
        &search_flags.show_hit_info, "show-hit-info",
        "Pass this flag to output information on each fine BLAST hit in "
        "CaBLAST_hits.txt.");
    opt_flag_bool(conf,
        &search_flags.hide_progress, "hide-progress",
        "Pass this flag to hide messages about the progress of CaBLAST as well "
        "as the progress bar for hit expansion.");
    opt_flag_bool(conf,
        &search_flags.load_coarse_residues, "load-coarse-residues",
        "Pass this flag to load all residues from the coarse FASTA file into "
        "memory.  Not recommended for machines with limited memory.");
    opt_flag_bool(conf,
        &search_flags.load_coarse_links, "load-coarse-links",
        "Pass this flag to load all links from the coarse links file into "
        "memory.  Not recommended for machines with limited memory.");
    opt_flag_bool(conf,
        &search_flags.load_coarse_db, "load-coarse-db",
        "Pass this flag to load all residues from the coarse FASTA file and "
        "all links from the coarse links file into memory.  Equivalent to "
        "passing both --load-coarse-residues and --load-coarse-links.  Not "
        "recommended for machines with limited memory.");
    opt_flag_bool(conf,
        &search_flags.load_compressed_db, "load-compressed-db",
        "Pass this flag to load all compressed sequences from compressed.cb."
        "Not recommended for machines with limited memory.");
    opt_flag_bool(conf,
        &search_flags.fine_blast_db, "fine-blast-db",
        "Pass this flag to run makeblastdb on the expanded hits before running "
        "fine BLAST.");
    opt_flag_int(conf,
        &search_flags.link_block_size, "link-block-size", 30000,
        "The number of bases in the coarse FASTA file each vector used for "
        "grouping the links in the coarse database represents.");

    return conf;
}

struct opt_config *load_cablat_args(){
    struct opt_config *conf = opt_config_init();

    opt_flag_bool(conf,
        &cablat_flags.load_coarse_residues, "load-coarse-residues",
        "Pass this flag to load all residues from the coarse FASTA file into "
        "memory.  Not recommended for machines with limited memory.");
    opt_flag_bool(conf,
        &cablat_flags.load_coarse_links, "load-coarse-links",
        "Pass this flag to load all links from the coarse links file into "
        "memory.  Not recommended for machines with limited memory.");
    opt_flag_bool(conf,
        &cablat_flags.load_coarse_db, "load-coarse-db",
        "Pass this flag to load all residues from the coarse FASTA file and "
        "all links from the coarse links file into memory.  Equivalent to "
        "passing both --load-coarse-residues and --load-coarse-links.  Not "
        "recommended for machines with limited memory.");
    opt_flag_bool(conf,
        &cablat_flags.load_compressed_db, "load-compressed-db",
        "Pass this flag to load all compressed sequences from compressed.cb."
        "Not recommended for machines with limited memory.");
    opt_flag_int(conf,
        &cablat_flags.link_block_size, "link-block-size", 30000,
        "The number of bases in the coarse FASTA file each vector used for "
        "grouping the links in the coarse database represents.");
    opt_flag_string(conf,
        &cablat_flags.output_expanded_fasta, "output-expanded-fasta", "",
        "Pass this flag to output the FASTA file used as the target for fine "
        "BLAT with each expanded sequence's offset in the original "
        "uncompressed sequence in the header.");
    opt_flag_bool(conf,
        &cablat_flags.hide_progress, "hide-progress",
        "Pass this flag to hide messages about the progress of CaBLAT.");
    opt_flag_bool(conf,
        &cablat_flags.no_cleanup, "no-cleanup",
        "Pass this flag to keep the intermediate files, such as the numbered "
        "query and target files, the coarse BLAT output, and the fine query "
        "and target files.");
    opt_flag_bool(conf,
        &cablat_flags.number_queries, "number-queries",
        "Pass this flag to add a step for numbering the query sequences.  "
        "Recommended to be passed in to prevent errors in BLAT due to "
        "duplicate query sequence names.");
    opt_flag_bool(conf,
        &cablat_flags.number_targets, "number-targets",
        "Pass this flag to add a step for numbering the target sequences.  "
        "Recommended to be passed in to prevent errors in BLAT due to "
        "duplicate target sequence names.");
    opt_flag_bool(conf,
        &cablat_flags.complete_psl, "complete-psl",
        "Pass this flag to output a .psl file for the final output that "
        "contains information that is normally removed from .psl output in "
        "BLAT, including the names of queries and target sequences past the "
        "first whitespace character as well as the location of the hit within "
        "the original uncompressed sequence");

    return conf;
}

