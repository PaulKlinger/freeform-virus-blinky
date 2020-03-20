/* 
 * File:   sequence.h
 * Author: kling
 *
 * Created on 20 March 2020, 21:31
 */

#ifndef SEQUENCE_H
#define	SEQUENCE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    struct sequence {
        uint8_t *data;
        uint32_t n_bases;
    };

    const struct sequence sars_cov_2_sequence;


#ifdef	__cplusplus
}
#endif

#endif	/* SEQUENCE_H */

